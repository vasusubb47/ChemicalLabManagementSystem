
#include "../lib/main.hpp"
#include "../lib/util.hpp"
#include "../lib/component.hpp"
#include "../lib/userComponent.hpp"
#include "../lib/fileSave.hpp"
#include "../lib/logComponent.hpp"
#include "../lib/userLogComponent.hpp"

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
    UserLogComponent userLogComp = UserLogComponent();
    do {
        std::cout << "1> Insert Data, 2> View Data, 4> Quit\n";
        std::cin >> option;
        switch (option) {
            case 1: {
                std::cout << "1> User 2> userLog\n";
                std::cin >> option;
                if (option == 1) {
                    userComp.getComponentInput();
                }else if (option == 2) {
                    userLogComp.getComponentInput();
                }
                option = 0;
            }; break;
            case 2: {
                std::cout << "1> User 2> userLog\n";
                std::cin >> option;
                std::vector<std::string> data;
                std::string uid;
                std::cout << "Enter the Uid : " ;
                std::cin >> uid;
                if (option == 1) {
                    data = userComp.extractData(uid);
                }else if (option == 2) {
                    data = userLogComp.extractData(uid);
                }
                for (std::string usrD : data) {
                    std::cout << usrD << ", ";
                }
                option = 0;
            }; break;
        }
    } while (option != quit);
    return 0;
}
