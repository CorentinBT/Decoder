#include <algorithm>
#include <cmath>
#include <cstddef>
#include <numeric>

#include <boost/numeric/ublas/matrix_proxy.hpp>

#include <tbb/blocked_range.h>
#include <tbb/parallel_for_each.h>

#include "common/assert.h"

#include "STCEncoder.h"

namespace Encoder {
namespace STC {

namespace {

Vector<std::size_t> AbsSortByIndexes(const Vector<f64>& v, const std::size_t sparsity_bound) {

    Vector<std::size_t> idx(v.size());
    std::iota(idx.begin(), idx.end(), 0);
    // It is useless to sort elements above the sparsity of the vector
    std::partial_sort(idx.begin(), idx.begin() + sparsity_bound, idx.end(),
                      [&v](size_t i1, size_t i2) { return std::abs(v[i1]) > std::abs(v[i2]); });

    return idx;
}

} // namespace

Vector<f64> Sparsify(const Vector<f64>& v, const Vector<std::size_t>& sorted_indexes,
                     const std::size_t sparsity_bound, Action action) {
    const std::size_t D = v.size();
    Vector<f64> sparse_vector(D, 0.0);

    for (size_t i = 0; i < sparsity_bound; i++) {
        const auto higher_elem_index = sorted_indexes[i];

        if (action == Action::KeepMagnitude)
            sparse_vector(higher_elem_index) = v[higher_elem_index];
        else if (action == Action::KeepSign)
            sparse_vector(higher_elem_index) = std::copysign(1.0, v[higher_elem_index]);
    }

    return sparse_vector;
}

Vector<f64> Encode(const Vector<f64>& target, const f64 sparsity, Action action) {
    ASSERT_MSG(sparsity <= 1.0 && sparsity >= 0.0, "sparsity is a percentage");
    const std::size_t sparsity_bound =
        static_cast<std::size_t>(std::trunc(target.size() * sparsity));

    const auto sorted_indexes = AbsSortByIndexes(target, sparsity_bound);
    const auto sparsified_matrix = Sparsify(target, sorted_indexes, sparsity_bound, action);

    return sparsified_matrix;
}

Matrix<f64> Encode(const Matrix<f64>& target, const f64 sparsity, Action action) {
    ASSERT_MSG(sparsity <= 1.0 && sparsity >= 0.0, "sparsity is a percentage");

    const std::size_t N = target.size1();
    const std::size_t D = target.size2();

    Matrix<f64> res(N, D);

    tbb::parallel_for(tbb::blocked_range<std::size_t>(0, N),
                      [&](const tbb::blocked_range<std::size_t>& range) {
                          for (size_t i = range.begin(); i < range.end(); i++) {
                              auto curr_row = boost::numeric::ublas::row(target, i);
                              const auto encoded_row = Encode(curr_row, sparsity, action);
                              boost::numeric::ublas::row(res, i) = encoded_row;
                          }
                      });

    return res;
}

} // namespace STC

} // namespace Encoder
