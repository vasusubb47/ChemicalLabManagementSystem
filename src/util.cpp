
#include "../lib/util.hpp"

uint64_t CLMS::getCurrentTime () {
    auto t = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(t.time_since_epoch()).count();
}

void CLMS::openFile(std::fstream& file, const std::string fileName, const std::string extension, const std::string dirName, std::ios_base::openmode mode) {
    std::cout << "Open file " << fileName << " with extension " << extension << "\n";
    file.open(std::string(Dir) + "\\" + dirName + "\\" + fileName + extension, mode);
}
