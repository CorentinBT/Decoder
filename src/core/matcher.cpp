#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

#include <tbb/blocked_range.h>
#include <tbb/blocked_range2d.h>
#include <tbb/concurrent_vector.h>
#include <tbb/parallel_for_each.h>
#include <tbb/parallel_sort.h>

#include <boost/numeric/ublas/vector_proxy.hpp>

#include "common/assert.h"

#include "core/matcher.h"

namespace Matcher {

namespace {

bool NearlyEqual(const double a, const double b) {
    const double eps = std::numeric_limits<double>::epsilon();

    return std::abs(a - b) <= eps;
}

} // namespace

Vector<std::size_t> Match(const Vector<f64>& vec, const Matrix<f64>& database, const u64 threshold,
                          Policy policy) {
    ASSERT_MSG(vec.size() == database.size2(),
               "vector should have the same number of column that the database");
    if (policy == Policy::FixedThreshold)
        ASSERT_MSG(threshold <= vec.size(), "threshold cannot be higher than the input vector");

    const std::size_t N = database.size1();
    const std::size_t D = database.size2();

    Vector<u64> indexes_score(N, 0);

    tbb::parallel_for(
        tbb::blocked_range2d<std::size_t>(0, D, 0, N),
        [&indexes_score, &database, &vec](const tbb::blocked_range2d<std::size_t>& range) {
            for (std::size_t i = range.rows().begin(); i < range.rows().end(); i++) {
                const auto curr_elem = vec(i);
                if (NearlyEqual(curr_elem, 0.0))
                    continue;

                for (std::size_t j = range.cols().begin(); j < range.cols().end(); j++) {
                    if (NearlyEqual(database(j, i), curr_elem))
                        ++indexes_score(j);
                }
            }
        });

    if (policy == Policy::FixedResList) {

        Vector<std::size_t> idx(N);
        std::iota(idx.begin(), idx.end(), 0);

        std::partial_sort(idx.begin(), idx.begin() + threshold, idx.end(),
                          [&indexes_score](const u64 i1, const u64 i2) {
                              return indexes_score[i1] > indexes_score[i2];
                          });

        return boost::numeric::ublas::subrange(idx, 0, threshold);
    } else if (policy == Policy::FixedThreshold) {

        // To avoid concurrent push_back
        tbb::concurrent_vector<std::size_t> idx;

        tbb::parallel_for(tbb::blocked_range<std::size_t>(0, N),
                          [&](const tbb::blocked_range<std::size_t>& range) {
                              for (size_t i = range.begin(); i < range.end(); i++) {
                                  if (indexes_score(i) >= threshold)
                                      idx.push_back(i);
                              }
                          });

        Vector<std::size_t> res(idx.size());
        std::copy(idx.begin(), idx.end(), res.data().begin());

        return res;
    }

    UNREACHABLE();
}

} // namespace Matcher
