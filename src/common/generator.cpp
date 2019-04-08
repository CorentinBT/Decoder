#include <random>

#include <tbb/blocked_range2d.h>
#include <tbb/parallel_for_each.h>

#include "common/generator.h"

namespace Generator {

static std::random_device rd{};
static std::mt19937 gen{rd()};

namespace Normal {

Matrix<double> Generate(const size_t M, const size_t N, const double mean, const double var) {

    std::normal_distribution<double> d{mean, var};
    Matrix<double> v(M, N);

    tbb::parallel_for(tbb::blocked_range2d<std::size_t>(0, M, 0, N),
                      [&v, &d](const tbb::blocked_range2d<std::size_t>& range) {
                          for (std::size_t i = range.rows().begin(); i < range.rows().end(); i++) {
                              for (std::size_t j = range.cols().begin(); j < range.cols().end();
                                   j++) {
                                  v(i, j) = d(gen);
                              }
                          }
                      });

    return v;
}

} // namespace Normal

namespace Uniform {

s64 Generate(const s64 min, const s64 max) {
    std::uniform_int_distribution<s64> uni(min, max);
    return uni(rd);
}

} // namespace Uniform

} // namespace Generator
