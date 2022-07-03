
#include "../lib/util.hpp"

uint64_t CLMS::getCurrentTime () {
    auto t = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(t.time_since_epoch()).count();
}

void CLMS::openFile(std::fstream& file, std::string filePath, std::ios_base::openmode mode) {
    if (file.is_open()) {
        file.close();
    }
    // std::cout << "opening the file : " << filePath << "\n";
    file.open(filePath, mode);
}

std::string CLMS::getFilePath(std::string filename, std::vector<std::string> dirChain, FileType fileType){
    std::string path = std::string(Dir);
    for (std::string dir : dirChain) {
        path += dir + "\\";
    }
    std::string ext;
    switch (fileType) {
        case FileType::DataFile : ext = ".dat"; break;
        case FileType::IndexFile : ext = ".ind"; break;
        case FileType::LogFile : ext = ".log"; break;
        case FileType::LogIndexFile : ext = ".ind"; break;
        case FileType::IndexKeyFile : ext = ".indk"; break;
        case FileType::IndexValueFile : ext = ".indv"; break;
        case FileType::CSV : ext = ".csv"; break;
        case FileType::TSV : ext = ".tsv"; break;
        case FileType::JSON : ext = ".json"; break;
    }
    path += filename + ext;
    return path;
}
