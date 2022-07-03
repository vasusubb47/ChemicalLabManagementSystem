
#include "../lib/component.hpp"

CLMS::Component::Component(const std::string& componentName, ComponentType componentType, std::vector<std::string> dirChain) {
    this->componentName = componentName;
    this->componentType = componentType;
    this->dirChain = dirChain;
    std::cout << "Component: " << componentName << "\n";
}

CLMS::Component::Component(const CLMS::Component& component) {
    this->componentName = component.componentName;
    this->componentType = component.componentType;
    this->dirChain = component.dirChain;
    std::cout << "Component (ref): " << componentName << "\n";
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

std::vector<std::string> CLMS::Component::extractData(const std::string id){
    FileType fileType;
    if (this->componentType == ComponentType::DataComponent) {
        fileType = FileType::DataFile;
    }else if (this->componentType == ComponentType::LogComponent) {
        fileType = FileType::LogFile;
    }
    openFile(this->componentFile, getFilePath(this->componentName, this->dirChain, fileType), std::ios::in);
    std::string line = "";
    auto val = this->index.find(id);
    if (val != this->index.end()) {
        this->componentFile.seekg(val->second);
        this->componentFile >> line;
    }
    if (line.size() == 0) {
        return {};
    }
    std::vector<std::string> vect;
    std::string delimiter = "|";
    size_t pos = 0;
    std::string temp_str;
    int count = 0;
    line.erase(0, 1);
    while((pos = line.find(delimiter)) != std::string::npos){
        temp_str = line.substr(0, pos);
        vect.emplace_back(temp_str);
        count++;
        line.erase(0, pos + delimiter.length());
    }
    return vect;
}

void CLMS::Component::loadIndex() {
    FileType fileType;
    if (this->componentType == ComponentType::DataComponent) {
        fileType = FileType::IndexFile;
    }else {
        fileType = FileType::LogIndexFile;
    }
    openFile(this->componentIndexFile, getFilePath(this->componentName, this->dirChain, fileType), std::ios::in);
    std::string data = "";
    this->componentIndexFile >> data;
    if (data.size() > 0) {
        std::cout << data << "\n";
        std::string delimiter = "#";
        size_t pos = 0;
        std::string temp_str;
        std::string length = data.substr(1, 5);
        this->index = std::unordered_map<std::string, uint32_t>(std::atoi(length.c_str()));
        data.erase(0, 6);
        while((pos = data.find(delimiter)) != std::string::npos){
            temp_str = data.substr(0, pos);
            size_t perDel = temp_str.find('%'), colDel = temp_str.find(':');
            this->index.insert({
                temp_str.substr(perDel + 1, colDel - 1),
                std::atoi(temp_str.substr(colDel + 1).c_str())
            });
            data.erase(0, pos + delimiter.length());
        }
        for(auto i = this->index.begin() ; i != this->index.end() ; i++){
            std::cout << i->first << ", " << i->second << "\n";
        }
    }else {
        openFile(this->componentIndexFile, getFilePath(this->componentName, this->dirChain, fileType), std::ios::out);
        this->componentIndexFile << "%0000#";
    }
}

uint32_t CLMS::Component::writeDataAndUpdateIndex(const std::string& PackedData, const std::string id, const uint16_t width) {
    if (this->componentType == ComponentType::DataComponent) {
        openFile(this->componentFile, getFilePath(this->componentName, this->dirChain, FileType::DataFile), std::ios::app);
    }else {
        openFile(this->componentFile, getFilePath(this->componentName, this->dirChain, FileType::LogFile), std::ios::app);
    }
    uint32_t biteOffSet = this->writeData(
        this->componentFile,
        -1,
        PackedData,
        width,
        '*'
    );
    if (this->componentType == ComponentType::DataComponent) {
        openFile(this->componentIndexFile, getFilePath(this->componentName, this->dirChain, FileType::IndexFile), std::ios::app);
    }else {
        openFile(this->componentIndexFile, getFilePath(this->componentName, this->dirChain, FileType::LogIndexFile), std::ios::app);
    }
    this->index.insert({id, biteOffSet});
    this->componentIndexFile << "%" << id << ":" << biteOffSet << "#";
    return biteOffSet;
}
