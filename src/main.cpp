
#include "../lib/main.hpp"
#include "../lib/util.hpp"
#include "../lib/fileSave.hpp"
#include "../lib/component.hpp"
#include "../lib/userComponent.hpp"
#include "../lib/chemicalComponent.hpp"
#include "../lib/logComponent.hpp"
#include "../lib/userLogComponent.hpp"
#include "../lib/chemicalLogComponent.hpp"

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
    ChemicalComponent chemicalComp = ChemicalComponent();
    UserLogComponent userLogComp = UserLogComponent();
    ChemicalLogComponent chemicalLogComp = ChemicalLogComponent();

    do {
        std::cout << "1> Insert Data, 2> View Data, 4> Quit\n";
        std::cin >> option;
        switch (option) {
            case 1: {
                std::cout << "1> User 2> userLog 3> Chemical 4> ChemicalLog\n";
                std::cin >> option;
                if (option == 1) {
                    userComp.getComponentInput();
                }else if (option == 2) {
                    userLogComp.getComponentInput();
                }else if (option == 3) {
                    chemicalComp.getComponentInput();
                }else if (option == 4) {
                    chemicalLogComp.getComponentInput();
                }
                option = 0;
            }; break;
            case 2: {
                std::cout << "1> User 2> userLog\n";
                std::cin >> option;
                std::vector<std::string> data;
                std::string id;
                std::cout << "Enter the id : " ;
                std::cin >> id;
                if (option == 1) {
                    data = userComp.extractData(id);
                }else if (option == 2) {
                    data = userLogComp.extractData(id);
                }else if (option == 3) {
                    data = chemicalComp.extractData(id);
                }else if (option == 4) {
                    data = chemicalLogComp.extractData(id);
                }
                for (std::string usrD : data) {
                    std::cout << usrD << ", ";
                }
                std::cout << std::endl;
                option = 0;
            }; break;
        }
    } while (option != quit);
    return 0;
}
