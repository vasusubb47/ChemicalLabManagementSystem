
#include "../lib/main.hpp"
#include "../lib/util.hpp"
#include "../lib/component.hpp"
#include "../lib/userComponent.hpp"

int main(int argc, char** argv) {
    CLMS::UserComponent userComp = CLMS::UserComponent();
    for (std::string head : userComp.getHeaders()) {
        std::cout << head << " ";
    }
    std::cout << "\n";
    userComp.getComponentInput();
    std::string id;
    std::cout << "Enter the ID : ";
    std::cin >> id;
    std::shared_ptr<void> userData = userComp.unpackData(id);
    CLMS::UserComponent::User* usr = (CLMS::UserComponent::User*)userData.get();
    std::cout << "User " << usr->print() << "\n";
    return 0;
}
