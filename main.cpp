#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    std::ifstream arquivo(argv[1]);

    if (!arquivo) {
        std::cout << "n da pra abrir \n";
        return 1;
    }