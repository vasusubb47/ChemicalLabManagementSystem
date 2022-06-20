
#pragma once

#include "main.hpp"
#include "util.hpp"

namespace CLMS {
    class FileSave {
        public:

            enum FileType {
                CSV, TSV, JSON
            };

        private:

            FileType fileType;
            std::string filename;
            std::ofstream outputFile;
            std::vector<std::string> headers;
            int numberOfRowsAdded;

            void writeHeadder();
            void writeFooter();

        public:

            FileSave(std::string filename, FileType fileType, std::vector<std::string> headers);
            FileSave(FileSave* fileSave);
            ~FileSave();

            void writeData(std::vector<std::string> data);

    };
}
