
#pragma once

#include "main.hpp"
#include "util.hpp"

namespace CLMS {

    class Component {
        protected:

            std::string componentName, componentFileName;
            std::map<std::string, uint32_t> index;
            std::fstream componentFile;

        public:

            Component(const std::string& componentName, const std::string& componentFileName);
            Component(const Component& component);
            ~Component();

            std::string getPackedData(const std::string& componentId, char del);
            void unpackData(const std::string& data);
            void writeData(const std::string& packedData, uint16_t width, char fill);
            void getComponentInput();
            std::vector<std::string> getHeaders();
            std::vector<std::string> getData(const std::string& componentId);

    };

}
