#pragma once

#include <vector>

#include "common/common_types.h"

namespace Matcher {

enum class Policy : u8 { FixedResList, FixedThreshold };

Vector<std::size_t> Match(const Vector<f64>& vec, const Matrix<f64>& database, const u64 threshold,
                          Policy policy = Policy::FixedThreshold);

} // namespace Matcher
