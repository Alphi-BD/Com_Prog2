#include <iostream>
#include <string>

int main() {
    std::cout << "Hello, CP2!" << std::endl;

    std::string name;
    while (std::getline(std::cin, name)) {
        std::cout << "Hello, " << name << std::endl;
    }

    return 0;
}
