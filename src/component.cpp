
#include "../lib/component.hpp"

CLMS::Component::Component(const std::string& componentName, ComponentType componentType) {
    this->componentName = componentName;
    this->componentType = componentType;
    
    if (this->componentType == CLMS::Component::ComponentType::DataComponent) {
        openFile(this->componentFile, this->componentName, ".dat", "log\\user", std::ios::in | std::ios::app);
        openFile(this->componentIndexFile, this->componentName, ".ind", "log\\user", std::ios::in | std::ios::app);
    }else {
        openFile(this->componentFile, this->componentName, ".log", "log\\user", std::ios::in | std::ios::app);
        openFile(this->componentIndexFile, this->componentName, ".ledg", "log\\user", std::ios::in | std::ios::app);
    }
}

CLMS::Component::Component(const CLMS::Component& component) {
    this->componentName = component.componentName;
    this->componentType = component.componentType;
    
    if (this->componentType == CLMS::Component::ComponentType::DataComponent) {
        openFile(this->componentFile, this->componentName, ".dat", "log\\user", std::ios::in | std::ios::app);
        openFile(this->componentIndexFile, this->componentName, ".ind", "log\\user", std::ios::in | std::ios::app);
    }else {
        openFile(this->componentFile, this->componentName, ".log", "log\\user", std::ios::in | std::ios::app);
        openFile(this->componentIndexFile, this->componentName, ".ledg", "log\\user", std::ios::in | std::ios::app);
    }
}

CLMS::Component::~Component() {
    this->componentFile.close();
    this->componentIndexFile.close();
}

uint32_t CLMS::Component::writeData(std::iostream& stream, const uint32_t biteOffSet, const std::string& packedData, uint16_t width,char fill) {
    if(biteOffSet != -1) {
        stream.seekg(biteOffSet);
    }
    stream << std::setw(width) << std::setfill(fill) << std::setiosflags(std::ios_base::left) << packedData << "\n";
    return ((uint32_t)stream.tellg() - width - 2);
}
