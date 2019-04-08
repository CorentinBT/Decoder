#include <fstream>

#include <nlohmann/json.hpp>

#include "common/assert.h"

#include "core/STCEncoder.h"
#include "core/matcher.h"

#include "config/config.h"
#include "config/settings.h"

Config::Config() : config_loc("config.json") {
    Reload();
}

void Config::ReadJSONValues() {

    std::ifstream i(config_loc);
    nlohmann::json j;
    i >> j;

    Settings::values.encoder_sparsity = j["parameters"]["encoder"]["sparsity"].get<f64>();

    Settings::values.matcher_threshold = j["parameters"]["matcher"]["threshold"].get<u64>();

    Settings::values.enable_chronos = j["parameters"]["miscellaneous"]["enableChronos"].get<bool>();

    Settings::values.encoder_policy = [&j]() {
        if (j["parameters"]["encoder"]["policy"].get<std::string>() == "KeepSign")
            return Encoder::STC::Action::KeepSign;
        else if (j["parameters"]["encoder"]["policy"].get<std::string>() == "KeepMagnitude")
            return Encoder::STC::Action::KeepMagnitude;
        UNREACHABLE();
    }();

    Settings::values.matcher_policy = [&j]() {
        if (j["parameters"]["matcher"]["policy"].get<std::string>() == "FixedResList")
            return Matcher::Policy::FixedResList;
        else if (j["parameters"]["matcher"]["policy"].get<std::string>() == "FixedThreshold")
            return Matcher::Policy::FixedThreshold;
        UNREACHABLE();
    }();

    Settings::values.db_filename = j["files"]["databaseFile"].get<std::string>();
    Settings::values.input_vec_filename = j["files"]["inputVectorFile"].get<std::string>();
    Settings::values.output_indexes_filename = j["files"]["outputIndexesFile"].get<std::string>();
}

void Config::Reload() {
    ReadJSONValues();
}
