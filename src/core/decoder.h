#pragma once

#include "common/common_types.h"

namespace Decoder {

	Vector<std::size_t> Decode(const Matrix<f64>& database, const Vector<f64>& vec);

}