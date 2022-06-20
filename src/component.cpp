
#include "../lib/component.hpp"

CLMS::Component::Component(const std::string& componentName, ComponentType componentType) {
    this->componentName = componentName;
    this->componentType = componentType;
    
    if (this->componentType == CLMS::Component::ComponentType::DataComponent) {
        this->componentFile.open(this->componentName + ".dat", std::ios::in | std::ios::app);
        this->componentIndexFile.open(this->componentName + ".ind", std::ios::in);
    }else {
        this->componentIndexFile.open(this->componentName + ".log", std::ios::in | std::ios::app);
        this->componentIndexFile.open(this->componentName + ".ledg", std::ios::in);
    }
}

CLMS::Component::Component(const CLMS::Component& component) {
    this->componentName = component.componentName;
    this->componentType = component.componentType;

    if (this->componentType == CLMS::Component::ComponentType::DataComponent) {
        this->componentFile.open(this->componentName + ".dat", std::ios::in | std::ios::app);
        this->componentIndexFile.open(this->componentName + ".ind", std::ios::in);
    }else {
        this->componentIndexFile.open(this->componentName + ".log", std::ios::in | std::ios::app);
        this->componentIndexFile.open(this->componentName + ".ledg", std::ios::in);
    }
}

CLMS::Component::~Component() {
    this->componentFile.close();
    this->componentIndexFile.close();
}

uint32_t CLMS::Component::writeData(const std::string& packedData, uint16_t width,char fill) {
    this->componentFile << std::setw(width) << std::setfill(fill) << std::setiosflags(std::ios_base::left) << packedData << "\n";
    this->componentFile.flush();
    return ((uint32_t)this->componentFile.tellg() - width - 2);
}
