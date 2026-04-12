#include <iostream>
#include <string>

using namespace std;

int main (int argc, char **argv) {
    if (argc < 2) {
        cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
        cout << endl;
        return (0);
    }

    for (size_t i = 1; i < (size_t)argc; i++){
        string input = argv[i];

        for (size_t j = 0; j < input.length(); j++) {
            cout << (char)toupper(input[j]);
        }
    }
    cout << endl;

    return (0);
}