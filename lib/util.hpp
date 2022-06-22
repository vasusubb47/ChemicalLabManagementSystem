
#ifndef UTIL_HPP
#define UTIL_HPP

#include "main.hpp"

#define TIME std::chrono::steady_clock::time_point

namespace CLMS {

    enum Type {
        INT, STRING
    };

    uint64_t getCurrentTime();

    void openFile(std::fstream& file, const std::string fileName, const std::string extension, const std::string dirName, std::ios_base::openmode mode);
    
}

#endif
