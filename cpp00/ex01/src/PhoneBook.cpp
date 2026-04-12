#include "PhoneBook.hpp"
#include "Contact.hpp"

using namespace std;

PhoneBook::PhoneBook() {
    count = 0;
    index = 0;
}

void PhoneBook::addContact() {
    string first;
    string last;
    string nick;
    string pn;
    string ds;

    do {
        cout << "Enter first name: ";
        getline(cin, first);
        if (first.empty())
            cout << "First name cannot be empty. Please try again." << endl;
    } while (first.empty());

    do {
        cout << "Enter last name: ";
        getline(cin, last);
        if (last.empty())
            cout << "Last name cannot be empty. Please try again." << endl;
    } while (last.empty());

    do {
        cout << "Enter nickname: ";
        getline(cin, nick);
        if (nick.empty())
            cout << "Nickname cannot be empty. Please try again." << endl;
    } while (nick.empty());

    do {
        cout << "Enter phone number: ";
        getline(cin, pn);
        if (pn.empty())
            cout << "Phone number cannot be empty. Please try again." << endl;
    } while (pn.empty());

    do {
        cout << "Enter darkest secret: ";
        getline(cin, ds);
        if (ds.empty())
            cout << "Darkest secret cannot be empty. Please try again." << endl;
    } while (ds.empty());

    contacts[index].setFirstName(first);
    contacts[index].setLastName(last);
    contacts[index].setNickname(nick);
    contacts[index].setPhoneNumber(pn);
    contacts[index].setDarkestSecret(ds);
    
    index = (index + 1) % 8;
    if (count < 8)
        count++;
    return;
}

void PhoneBook::searchContacts() {
    if (count == 0) {
        cout << "No contacts saved yet..." << endl;
        return;
    }

    cout << "|";
    cout << setw(10) << "Index" << "|";
    cout << setw(10) << "First Name" << "|";
    cout << setw(10) << "Last Name" << "|";
    cout << setw(10) << "Nickname" << "|";
    cout << endl;

    for (int i = 0; i < count; i++) {
        string first = contacts[i].getFirstName();
        string last = contacts[i].getLastName();
        string nick = contacts[i].getNickname();

        if (first.length() > 10) {
            first = first.substr(0, 9) + ".";
        }

        if (last.length() > 10) {
            last = last.substr(0, 9) + ".";
        }

        if (nick.length() > 10) {
            nick = nick.substr(0, 9) + ".";
        }

        cout << "|";
        cout << setw(10) << i << "|";
        cout << setw(10) << first << "|";
        cout << setw(10) << last << "|";
        cout << setw(10) << nick << "|";
        cout << endl;
    }

    string input;
    int selected;
    
    cout << "\nEnter the index of the contact to display: ";
    getline(cin, input);
    
    // Convert string to int and validate
    try {
        selected = stoi(input);
        if (selected < 0 || selected >= count) {
            cout << "Error: Index out of range. Valid range is 0 to " << (count - 1) << endl;
            return;
        }
        displayContact(selected);
    } catch (...) {
        cout << "Error: Invalid input. Please enter a valid number." << endl;
    }
}

void PhoneBook::displayContact(int i) {
    if (i < 0 || i >= count) {
        cout << "Invalid index!" << endl;
        return;
    }
    
    cout << "\n=== Contact Details ===" << endl;
    cout << "First Name: " << contacts[i].getFirstName() << endl;
    cout << "Last Name: " << contacts[i].getLastName() << endl;
    cout << "Nickname: " << contacts[i].getNickname() << endl;
    cout << "Phone Number: " << contacts[i].getPhoneNumber() << endl;
    cout << "Darkest Secret: " << contacts[i].getDarkestSecret() << endl;
    cout << "======================" << endl;
}