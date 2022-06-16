
#ifndef UTIL_HPP
#define UTIL_HPP

#include "main.hpp"

#define TIME std::chrono::steady_clock::time_point

namespace CLMS {

    enum Type {
        INT, STRING
    };

    uint64_t getCurrentTime();
    
}

#endif
