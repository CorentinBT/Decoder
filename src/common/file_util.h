#pragma once

#include <fstream>
#include <limits>
#include <string>
#include <type_traits>

#include <boost/numeric/ublas/io.hpp>

#include "common/common_types.h"

#include "common/timer.h"

namespace FileUtil {

class IOFile : public NonCopyable {
public:
    IOFile() = default;
    IOFile(const std::string& filename);

    ~IOFile() = default;

    bool Open(const std::string& filename);
    bool Close();

	template <typename T>
    T Read() {
        if (IsOpen()) {
            Common::Timer timer;
            timer.Start();
            std::ios_base::sync_with_stdio(false);
            T res;
            m_file >> res;
            timer.Stop();

			std::cout << timer.GetTimeElapsed() << '\n';

            return res;
        }
        return {};
    }

	template <typename T>
    void Write(const T& data) {
        if (IsOpen()) {
            std::ios_base::sync_with_stdio(false);
            m_file << data;
        }
    }

    bool IsOpen() const {
        return m_file.is_open();
    }

private:
    std::fstream m_file;
};

} // namespace FileUtil
