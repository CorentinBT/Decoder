#pragma once

#include "common/common_types.h"

namespace Encoder {
namespace STC {

enum class Action : u8 { KeepSign, KeepMagnitude };

Vector<f64> Encode(const Vector<f64>& target, const f64 sparsity,
                   Action action = Action::KeepSign);
Matrix<f64> Encode(const Matrix<f64>& target, const f64 sparsity,
                   Action action = Action::KeepSign);

} // namespace STC

} // namespace Encoder
