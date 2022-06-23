
#include "../lib/main.hpp"
#include "../lib/util.hpp"
#include "../lib/component.hpp"
#include "../lib/userComponent.hpp"
#include "../lib/fileSave.hpp"

using namespace CLMS;

int main(int argc, char** argv) {
    // creating all the folders required by the project
    // all the folders will be created at initial run of the project
    std::filesystem::create_directories(Dir);
    std::filesystem::create_directories(std::string(Dir) + "\\log");
    std::filesystem::create_directories(std::string(Dir) + "\\log\\user");
    std::filesystem::create_directories(std::string(Dir) + "\\log\\chemical");
    std::filesystem::create_directories(std::string(Dir) + "\\component");
    std::filesystem::create_directories(std::string(Dir) + "\\component\\user");
    std::filesystem::create_directories(std::string(Dir) + "\\component\\chemical");
    
    system("cls");
    int option;
    const int quit = 4;
    UserComponent userComp = UserComponent();
    do {
        std::cout << "1> Insert Data, 2> View Data, 4> Quit\n";
        std::cin >> option;
        switch (option) {
            case 1: {
                userComp.getComponentInput();
            }; break;
            case 2: {
                std::string uid;
                std::cout << "Enter the Uid : " ;
                std::cin >> uid;
                std::vector<std::string> data = userComp.extractData(uid);
                for (std::string usrD : data) {
                    std::cout << usrD << ", ";
                }
                std::cout << std::endl;
                // std::shared_ptr<void> data = userComp.unpackData(uid);
                // UserComponent::User* user = (UserComponent::User*)data.get();
                // std::cout << "user : " << user->print() << std::endl;
            }; break;
        }
    } while (option != quit);
    return 0;
}
