
#pragma once

#include "main.hpp"
#include "util.hpp"

namespace CLMS {

    class Component {
        protected:

            std::string componentName;
            ComponentType componentType;
            std::unordered_map<std::string, uint32_t> index;
            std::fstream componentFile;
            std::fstream componentIndexFile;

            std::vector<std::string> dirChain;

        public:

            Component(const std::string& componentName, const ComponentType, std::vector<std::string> dirChain);
            Component(const Component& component);
            ~Component();
            
            std::string getPackedData(const void* data, const char del);
            std::shared_ptr<void> unpackData(const std::string id);
            std::vector<std::string> extractData(const std::string id);
            void loadIndex();
            uint32_t writeDataAndUpdateIndex(const std::string& PackedData, const std::string id, const uint16_t width);
            uint32_t writeData(std::iostream& stream, const uint32_t biteOffSet, const std::string& packedData, uint16_t width, char fill);
            void getComponentInput();
            std::vector<std::string> getHeaders();

            void saveAs() {}

    };

}
