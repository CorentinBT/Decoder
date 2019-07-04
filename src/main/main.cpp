#include <iostream>
#include <string>
#include <vector>

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

#include "common/common_types.h"
#include "common/npy/cnpy.h"
#include "common/timer.h"

#include "config/config.h"
#include "config/settings.h"

#include "core/decoder.h"

int main(int argc, char* argv[]) {

    Config config;

    Common::Timer t;
    t.Start();
    const auto mat = cnpy::npy_load(Settings::values.db_filename);
    const auto shape = mat.shape;
    const auto N = shape[0];
    const auto D = shape[1];

    Matrix<f64> database(N, D);
    std::copy(mat.data<f64>(), mat.data<f64>() + N * D, database.data().begin());
    t.Stop();

    if (Settings::values.enable_chronos)
        std::cout << "Time to load the database : " << t.GetTimeElapsed() << "ms\n";

    const auto encoded_database = Encoder::STC::Encode(database, Settings::values.encoder_sparsity,
                                                       Settings::values.encoder_policy);

    Vector<f64> input_vec(D);
    const auto vec = cnpy::npy_load(Settings::values.input_vec_filename);
    std::copy(vec.data<f64>(), vec.data<f64>() + D, input_vec.data().begin());

    const auto encoded_input_vec = Encoder::STC::Encode(
        input_vec, Settings::values.encoder_sparsity, Settings::values.encoder_policy);

    const auto matching_indexes = Decoder::Decode(database, encoded_input_vec);

    cnpy::npy_save(Settings::values.output_indexes_filename, &(matching_indexes.data())[0],
                   {matching_indexes.size()}, "w");

    std::cout << matching_indexes.size() << " matching elements have been found. Writing them on "
              << Settings::values.output_indexes_filename << '\n';

    return 0;
}
