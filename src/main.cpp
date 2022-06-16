
#include "../lib/main.hpp"
#include "../lib/util.hpp"
// #include "../lib/config.hpp"

int main(int argc, char** argv) {
    // CLMS::loadConfig();
    // CLMS::printConfig();
    int i = 0;
    while (i < 99) {
        std::cout << "(" << (i+1) << ") Current Time : " << CLMS::getCurrentTime() << " :: " << CLMS::getCurrentTime() << "\n";
        i++;
    }
    return 0;
}
