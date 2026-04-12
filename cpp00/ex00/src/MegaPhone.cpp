#include <iostream>
#include <string>

int main (int argc, char **argv) {
    if (argc < 2) {
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
        std::cout << std::endl;
        return (0);
    }

    for (size_t i = 1; i < (size_t)argc; i++){
        std::string input = argv[i];

        for (size_t j = 0; j < input.length(); j++) {
            std::cout << (char)toupper(input[j]);
        }
    }
    std::cout << std::endl;

    return (0);
}