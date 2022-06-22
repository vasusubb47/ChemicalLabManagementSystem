
#pragma once

#include "main.hpp"
#include "util.hpp"

namespace CLMS {

    class Component {
        public:
            enum ComponentType {
                DataComponent, LogComponent
            };

        protected:

            std::string componentName;
            ComponentType componentType;
            std::unordered_map<std::string, uint32_t> index;
            std::fstream componentFile;
            std::fstream componentIndexFile;

        public:

            Component(const std::string& componentName, const ComponentType);
            Component(const Component& component);
            ~Component();

            std::string getPackedData(const void* data, const char del);
            std::shared_ptr<void> unpackData(const std::string& data);
            uint32_t writeData(std::iostream& stream, const uint32_t biteOffSet, const std::string& packedData, uint16_t width, char fill);
            void getComponentInput();
            std::vector<std::string> getHeaders();
            std::string getData(const std::string& componentId);

    };

}
