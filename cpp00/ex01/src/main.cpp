#include "PhoneBook.hpp"
#include <iostream>

using namespace std;

int main(void) {
    PhoneBook phonebook;
    string command;
    
    cout << "Welcome to the PhoneBook!" << endl;
    cout << "Available commands: ADD, SEARCH, EXIT" << endl;
    
    while (true) {
        cout << "\nEnter a command: ";
        getline(cin, command);
        
        if (command == "ADD") {
            phonebook.addContact();
        }
        else if (command == "SEARCH") {
            phonebook.searchContacts();
        }
        else if (command == "EXIT") {
            cout << "Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid command. Please use ADD, SEARCH, or EXIT." << endl;
        }
    }
    
    return 0;
}