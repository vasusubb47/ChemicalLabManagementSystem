
#include "../lib/main.hpp"
#include "../lib/util.hpp"
#include "../lib/component.hpp"
#include "../lib/userComponent.hpp"
#include "../lib/fileSave.hpp"

using namespace CLMS;

int main(int argc, char** argv) {
    system(("mkdir " + std::string(Dir)).c_str());
    system("cls");
    int option;
    const int quit = 4;
    do {
        std::cout << "1> Insert Data, 2> View Data, 4> Quit\n";
        option = std::getchar();
    } while (option != quit);
    return 0;
}
