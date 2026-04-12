#include "PhoneBook.hpp"
#include <iostream>

int main(void) {
    PhoneBook phonebook;
    std::string command;

    std::cout << "Welcome to the PhoneBook!" << std::endl;
    std::cout << "Available commands: ADD, SEARCH, EXIT" << std::endl;

    while (true) {
        std::cout << "\nEnter a command: ";
        std::getline(std::cin, command);

        if (command == "ADD") {
            phonebook.addContact();
        }
        else if (command == "SEARCH") {
            phonebook.searchContacts();
        }
        else if (command == "EXIT") {
            std::cout << "Goodbye!" << std::endl;
            break;
        }
        else {
            std::cout << "Invalid command. Please use ADD, SEARCH, or EXIT." << std::endl;
        }
    }
    
    return 0;
}