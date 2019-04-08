#pragma once

#include "common/common_types.h"

namespace Generator {

namespace Normal {

Matrix<double> Generate(const std::size_t M, const std::size_t N, const double mean = 0.0,
                        const double var = 1.0);

} // namespace Normal

namespace Uniform {

s64 Generate(const s64 min, const s64 max);

}

} // namespace Generator
