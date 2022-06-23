
#include "../lib/userComponent.hpp"

CLMS::UserComponent::UserComponent() : Component("UserComponent", ComponentType::DataComponent, {"component", "User"}) {
    std::cout << "UserComponent\n";
    loadIndex();
}

CLMS::UserComponent::~UserComponent(){}

void CLMS::UserComponent::getComponentInput() {
    std::string Id, Name, Contact;
    std::cout << "Enter User Information : ";
    std::cin >> Id >> Name >> Contact;
    User user = User(
        Id, Name, Contact
    );
    this->writeDataAndUpdateIndex(this->getPackedData(&user, '|'), Id, 32);
}

std::string CLMS::UserComponent::getPackedData(const void* data, const char del) {
    const User* userData = (const User*)data;
    return std::string() + del + userData->Id + del + userData->Name + del + userData->Contact + del;
}

std::shared_ptr<void> CLMS::UserComponent::unpackData(const std::string componentId) {
    std::vector<std::string> compData = this->extractData(componentId);
    if (compData.size() == 0) {
        return std::make_shared<nullptr_t>(nullptr);
    }
    return std::make_shared<User>(new User(compData));
}

std::vector<std::string> CLMS::UserComponent::getHeaders() {
    return {"ID", "Name", "Contact"};
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

CLMS::UserComponent::User::User(std::vector<std::string> data) {
    this->Id = data[0];
    this->Name = data[1];
    this->Contact = data[2];
}

std::string CLMS::UserComponent::User::print() {
    return "{Id : " + this->Id + ", Name : " + this->Name + ", Contact : " + this->Contact + "}";
}
