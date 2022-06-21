
#include "../lib/userComponent.hpp"

CLMS::UserComponent::UserComponent() : Component("UserComponent", ComponentType::DataComponent) {
    std::cout << "UserComponent\n";
    std::string data;
    this->componentIndexFile >> data;
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
        //std::cout << temp_str.substr(temp_str.find('%')+1,6) << "," << temp_str.substr(temp_str.find(':')+1) << "\n";
        data.erase(0, pos + delimiter.length());
    }
    for(auto i = this->index.begin() ; i != this->index.end() ; i++){
        std::cout << i->first << ", " << i->second << "\n";
    }
    this->componentIndexFile.close();
    this->componentIndexFile.open(this->componentName + ".ind", std::ios::app);
}
CLMS::UserComponent::~UserComponent(){}

void CLMS::UserComponent::getComponentInput() {
    std::string Id, Name, Contact;
    std::cout << "Enter User Information : ";
    std::cin >> Id >> Name >> Contact;
    User user = User(
        Id, Name, Contact
    );
    std::string packedData =  this->getPackedData(&user, '|');
    uint32_t biteOffSet = this->writeData(packedData, 32, '*');
    this->index.insert({Id, biteOffSet});
    this->componentIndexFile << "%" << Id << ":" << biteOffSet << "#";
}

std::string CLMS::UserComponent::getPackedData(const void* data, const char del) {
    const User* userData = (const User*)data;
    return std::string() + del + userData->Id + del + userData->Name + del + userData->Contact + del;
}

std::shared_ptr<void> CLMS::UserComponent::unpackData(const std::string& componentId) {
    std::string compData = this->getData(componentId);
    if (compData.empty()) {
        return std::make_shared<std::nullptr_t>(nullptr);
    }
    std::string Id, Name, Contact;
    std::string arr[3];
    std::string delimiter = "|";
    size_t pos = 0;
    std::string temp_str;
    int count = 0;
    while((pos = compData.find(delimiter)) != std::string::npos){
        temp_str = compData.substr(0, pos);
        arr[count] = temp_str;
        count++;
        compData.erase(0, pos + delimiter.length());
    }
    Id = arr[1];
    Name = arr[2];
    Contact = arr[3];
    
    return std::make_shared<User>(new User(Id, Name, Contact));
}

std::vector<std::string> CLMS::UserComponent::getHeaders() {
    return {"ID", "Name", "Contact"};
}

std::string CLMS::UserComponent::getData(const std::string& componentId) {
    auto val = this->index.find(componentId);
    if (val != this->index.end()) {
        this->componentFile.seekg(val->second);
        std::string line;
        this->componentFile >> line;
        return line;
    }
    return "";
}

CLMS::UserComponent::User::User(const std::string Id, const std::string name, const std::string contact) {
    this->Id = Id;
    this->Name = name;
    this->Contact = contact;
}

CLMS::UserComponent::User::User(const CLMS::UserComponent::User* user) {
    this->Id = user->Id;
    this->Name = user->Name;
    this->Contact = user->Contact;
}

std::string CLMS::UserComponent::User::print() {
    return "{Id : " + this->Id + ", Name : " + this->Name + ", Contact : " + this->Contact + "}";
}
