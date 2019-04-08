#include "common/file_util.h"

namespace FileUtil {

IOFile::IOFile(const std::string& filename) {
    Open(filename);
}

bool IOFile::Open(const std::string& filename) {
    Close();

    m_file.open(filename, std::ios::in | std::ios::out | std::ios::binary);

    return IsOpen();
}

bool IOFile::Close() {
    if (!IsOpen())
        return false;

    m_file.close();
    return true;
}

} // namespace FileUtil
