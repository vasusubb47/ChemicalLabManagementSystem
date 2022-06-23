
#include "../lib/component.hpp"

CLMS::Component::Component(const std::string& componentName, ComponentType componentType, std::vector<std::string> dirChain) {
    this->componentName = componentName;
    this->componentType = componentType;
    this->dirChain = dirChain;
}

CLMS::Component::Component(const CLMS::Component& component) {
    this->componentName = component.componentName;
    this->componentType = component.componentType;
    this->dirChain = component.dirChain;
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

void CLMS::Component::open(CLMS::Component::ComponentFileType openFileType, std::ios_base::openmode mode){
    std::string path = std::string(Dir);
    for (std::string dir : this->dirChain) {
        path += dir + "\\";
    }
    std::string ext;
    switch (openFileType) {
        case ComponentFileType::DataFile : ext = ".dat"; break;
        case ComponentFileType::IndexFile : ext = ".ind"; break;
        case ComponentFileType::LogFile : ext = ".log"; break;
        case ComponentFileType::LogIndexFile : ext = ".ind"; break;
    }
    std::cout << "Opening the file : " << path << this->componentName << ext << std::endl;
    if (openFileType == ComponentFileType::DataFile || openFileType == ComponentFileType::LogFile) {
        if (this->componentFile.is_open()) {
            this->componentFile.close();
        }
        this->componentFile.open(path+this->componentName+ext, mode);
    }else if (openFileType == ComponentFileType::IndexFile || openFileType == ComponentFileType::LogIndexFile) {
        if (this->componentIndexFile.is_open()) {
            this->componentIndexFile.close();
        }
        this->componentIndexFile.open(path+this->componentName+ext, mode);
    }
}

std::vector<std::string> CLMS::Component::extractData(const std::string id){
    open(ComponentFileType::DataFile, std::ios::in);
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
    this->open(ComponentFileType::IndexFile, std::ios::in);
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
            this->index.insert({temp_str.substr(temp_str.find('%')+1,6), std::atoi(temp_str.substr(temp_str.find(':')+1).c_str())});
            data.erase(0, pos + delimiter.length());
        }
        for(auto i = this->index.begin() ; i != this->index.end() ; i++){
            std::cout << i->first << ", " << i->second << "\n";
        }
    }else {
        this->open(ComponentFileType::IndexFile, std::ios::out);
        this->componentIndexFile << "%0000#";
    }
}

void CLMS::Component::writeDataAndUpdateIndex(const std::string& PackedData, const std::string id, const uint16_t width) {
    if (this->componentType == ComponentType::DataComponent) {
        this->open(ComponentFileType::DataFile, std::ios::app);
    }else {
        this->open(ComponentFileType::LogFile, std::ios::app);
    }
    uint32_t biteOffSet = this->writeData(
        this->componentFile,
        -1,
        PackedData,
        width,
        '*'
    );
    if (this->componentType == ComponentType::DataComponent) {
        this->open(ComponentFileType::IndexFile, std::ios::app);
    }else {
        this->open(ComponentFileType::LogIndexFile, std::ios::app);
    }
    this->index.insert({id, biteOffSet});
    this->componentIndexFile << "%" << id << ":" << biteOffSet << "#";
    // this->componentIndexFile.seekg(std::ios::beg);
    // (std::ostream&)(this->componentIndexFile.seekg(std::ios::beg)) << "%" << std::setw(4) << std::setfill('0') << this->index.size() << "#";
    this->componentFile.flush();
    this->componentIndexFile.flush();
}
