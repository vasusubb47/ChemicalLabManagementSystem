
#include "../lib/userComponent.hpp"

CLMS::UserComponent::UserComponent() : Component("UserComponent") {
    std::cout << "UserComponent\n";
    std::string data;
    this->componentIndexFile >> data;
    std::cout << data << "\n";
    this->componentIndexFile.close();
    this->componentIndexFile.open(this->componentName + ".ind", std::ios::app);
}
CLMS::UserComponent::~UserComponent(){}

void CLMS::UserComponent::getComponentInput() {
    std::string Id, Name, Contact;
    std::cout << "Get Component Data: ";
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
    if (compData == "") {
        return std::make_shared<std::nullptr_t>(nullptr);
    }
    std::string Id, Name, Contact;
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
