
#include "common/timer.h"

#include "core/decoder.h"

#include "config/settings.h"

#include "core/STCEncoder.h"
#include "core/matcher.h"

namespace Decoder {

Vector<std::size_t> Decode(const Matrix<f64>& database, const Vector<f64>& vec) {

    const auto encoded_db = [&database]() {
        // Getting the correct overloaded function
        Matrix<f64> (&EncodeFunc)(const Matrix<f64>&, const f64, Encoder::STC::Action) =
            Encoder::STC::Encode;

        if (Settings::values.enable_chronos) {
            const auto time_return_pair =
                Common::TimeFunction(EncodeFunc, database, Settings::values.encoder_sparsity,
                                     Settings::values.encoder_policy);

            std::cout << "Encoding time : " << time_return_pair.first << "ms\n";
            return time_return_pair.second;
        } else {
            return Encoder::STC::Encode(database, Settings::values.encoder_sparsity,
                                        Settings::values.encoder_policy);
        }
    }();

    const auto encoded_vec = Encoder::STC::Encode(vec, Settings::values.encoder_sparsity,
                                                  Settings::values.encoder_policy);

    const auto matching_indexes = [&encoded_vec, &encoded_db]() {
        if (Settings::values.enable_chronos) {
            const auto time_return_pair = Common::TimeFunction(
                Matcher::Match, encoded_vec, encoded_db, Settings::values.matcher_threshold,
                Settings::values.matcher_policy);

            std::cout << "Matching time : " << time_return_pair.first << "ms\n";
            return time_return_pair.second;
        } else {
            return Matcher::Match(encoded_vec, encoded_db, Settings::values.matcher_threshold,
                                  Settings::values.matcher_policy);
        }
    }();

    return matching_indexes;
}

} // namespace Decoder
