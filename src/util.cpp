
#include "../lib/util.hpp"

uint64_t CLMS::getCurrentTime () {
    auto t = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(t.time_since_epoch()).count();
}
