#pragma once

#include <string>

#include "common/common_types.h"

#include "core/STCEncoder.h"
#include "core/matcher.h"

namespace Settings {

struct Values {
    // Encoder
    f64 encoder_sparsity;
    Encoder::STC::Action encoder_policy;
    // Matcher
    u64 matcher_threshold;
    Matcher::Policy matcher_policy;
    // Miscellaneous
    bool enable_chronos;
    // Files
    std::string db_filename;
    std::string input_vec_filename;
    std::string output_indexes_filename;

} extern values;

} // namespace Settings
