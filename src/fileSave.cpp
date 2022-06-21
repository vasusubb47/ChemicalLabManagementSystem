
#include "../lib/fileSave.hpp"

CLMS::FileSave::FileSave(std::string filename, FileType fileType, std::vector<std::string> headers) {
    this->filename = filename;
    this->fileType = fileType;
    this->headers = headers;
    this->numberOfRowsAdded = 0;
    std::string fileNameWithExt = filename;
    switch (this->fileType) {
        case FileType::CSV : fileNameWithExt += ".csv"; break;
        case FileType::TSV : fileNameWithExt += ".tsv"; break;
        case FileType::JSON : fileNameWithExt += ".json"; break;
    }
    this->outputFile.open(Dir + fileNameWithExt, std::ios::in | std::ios::trunc);
    this->writeHeadder();
}

CLMS::FileSave::FileSave(FileSave* fileSave) {
    this->filename = fileSave->filename;
    this->fileType = fileSave->fileType;
    this->headers = fileSave->headers;
    this->numberOfRowsAdded = 0;
    std::string fileNameWithExt = this->filename;
    switch (this->fileType) {
        case FileType::CSV : fileNameWithExt += ".csv"; break;
        case FileType::TSV : fileNameWithExt += ".tsv"; break;
        case FileType::JSON : fileNameWithExt += ".json"; break;
    }
    this->outputFile.open(Dir + fileNameWithExt, std::ios::in | std::ios::trunc);
    this->writeHeadder();
}

CLMS::FileSave::~FileSave() {
    this->writeFooter();
    this->outputFile.close();
}

void CLMS::FileSave::writeData(std::vector<std::string> data) {
    if (this->headers.size() != data.size()) {
        std::cout << "data did not match expected size\n";
        return;
    }
    if (this->fileType == FileType::CSV || this->fileType == FileType::TSV) {
        char del;
        if (this->fileType == FileType::TSV) {
            del = '\t';
        }else {
            del = ',';
        }
        int i = 0;
        for (; i < data.size() - 1; i++) {
            this->outputFile << data[i] << del;
        }
        this->outputFile << data[i] << "\n";        
    }else if(this->fileType == FileType::JSON) {
        if (numberOfRowsAdded == 0) {
            this->outputFile << "{";
        }else{
            this->outputFile << ",{";
        }
        int i = 0;
        for (; i < data.size() - 1; i++) {
            this->outputFile << "\"" << headers[i] << "\":\"" << data[i] << "\",";
        }
        this->outputFile << "\"" << headers[i] << "\":\"" << data[i] << "\"}";
    }
    numberOfRowsAdded++;
}

void CLMS::FileSave::writeHeadder() {
    if (this->fileType == FileType::CSV || this->fileType == FileType::TSV) {
        char del;
        if (this->fileType == FileType::TSV) {
            del = '\t';
        }else {
            del = ',';
        }
        int i = 0;
        for (; i < headers.size() - 1; i++) {
            this->outputFile << headers[i] << del;
        }
        this->outputFile << headers[i] << "\n";
    }else if(this->fileType == FileType::JSON) {
        this->outputFile << "[";
    }
}

void CLMS::FileSave::writeFooter() {
    if(this->fileType == FileType::JSON) {
        this->outputFile << "]";
    }
}
