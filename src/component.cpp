
#include "../lib/component.hpp"

CLMS::Component::Component(const std::string& componentName, const std::string& componentFileName) {
    this->componentName = componentName;
    this->componentFileName = componentFileName;
    this->index = std::map<std::string, uint32_t>();

    this->componentFile.open(this->componentFileName, std::ios::in | std::ios::app);
}

CLMS::Component::~Component() {
    this->componentFile.close();
}

void CLMS::Component::writeData(const std::string& packedData, uint16_t width,char fill) {
    this->componentFile << std::setw(width) << std::setfill(fill) << std::setiosflags(std::ios_base::left) << packedData;
}
