
#include "../lib/userComponent.hpp"

CLMS::UserComponent::UserComponent(const std::string& componentFileName) : Component("UserComponent", componentFileName) {}
CLMS::UserComponent::~UserComponent(){}

void CLMS::UserComponent::getComponentInput() {
    std::string Id, Name, Contact;
    std::cout << "Get Component Data: ";
    std::cin >> Id >> Name >> Contact;
    User user = User(
        Id, Name, Contact
    );
    std::cout << "{ Id : " << user.Id << ", Name : " << user.Name << ", Contact : " << user.Contact << "}\n";
}

std::string CLMS::UserComponent::getPackedData(const std::string& componentId, char del) {}

void CLMS::UserComponent::unpackData(const std::string& componentId) {}

std::vector<std::string> CLMS::UserComponent::getHeaders() {}

std::vector<std::string> CLMS::UserComponent::getData(const std::string& componentId) {}

CLMS::UserComponent::User::User(const std::string Id, const std::string name, const std::string contact) {
    this->Id = Id;
    this->Name = name;
    this->Contact = contact;
}
