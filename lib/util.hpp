
#ifndef UTIL_HPP
#define UTIL_HPP

#include "main.hpp"

#define TIME std::chrono::steady_clock::time_point

namespace CLMS {

    enum Type {
        INT, STRING
    };

    enum ComponentType {
        DataComponent, LogComponent
    };

    enum FileType{
        DataFile, IndexFile, LogFile, LogIndexFile, IndexKeyFile, IndexValueFile, CSV, TSV, JSON
    };

    uint64_t getCurrentTime();

    void openFile(std::fstream& file, std::string filePath, std::ios_base::openmode mode);
    std::string getFilePath(std::string filename, std::vector<std::string> dirChain, FileType fileType);

}

#endif
