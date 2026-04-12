#include "PhoneBook.hpp"
#include "Contact.hpp"

PhoneBook::PhoneBook() {
    count = 0;
    index = 0;
}

void PhoneBook::addContact() {
    std::string first;
    std::string last;
    std::string nick;
    std::string pn;
    std::string ds;

    do {
        std::cout << "Enter first name: ";
        std::getline(std::cin, first);
        if (first.empty())
            std::cout << "First name cannot be empty. Please try again." << std::endl;
    } while (first.empty());

    do {
        std::cout << "Enter last name: ";
        std::getline(std::cin, last);
        if (last.empty())
            std::cout << "Last name cannot be empty. Please try again." << std::endl;
    } while (last.empty());

    do {
        std::cout << "Enter nickname: ";
        std::getline(std::cin, nick);
        if (nick.empty())
            std::cout << "Nickname cannot be empty. Please try again." << std::endl;
    } while (nick.empty());

    do {
        std::cout << "Enter phone number: ";
        std::getline(std::cin, pn);
        if (pn.empty())
            std::cout << "Phone number cannot be empty. Please try again." << std::endl;
    } while (pn.empty());

    do {
        std::cout << "Enter darkest secret: ";
        std::getline(std::cin, ds);
        if (ds.empty())
            std::cout << "Darkest secret cannot be empty. Please try again." << std::endl;
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
        std::cout << "No contacts saved yet..." << std::endl;
        return;
    }

    std::cout << "|";
    std::cout << std::setw(10) << "Index" << "|";
    std::cout << std::setw(10) << "First Name" << "|";
    std::cout << std::setw(10) << "Last Name" << "|";
    std::cout << std::setw(10) << "Nickname" << "|";
    std::cout << std::endl;

    for (int i = 0; i < count; i++) {
        std::string first = contacts[i].getFirstName();
        std::string last = contacts[i].getLastName();
        std::string nick = contacts[i].getNickname();

        if (first.length() > 10) {
            first = first.substr(0, 9) + ".";
        }

        if (last.length() > 10) {
            last = last.substr(0, 9) + ".";
        }

        if (nick.length() > 10) {
            nick = nick.substr(0, 9) + ".";
        }

        std::cout << "|";
        std::cout << std::setw(10) << i << "|";
        std::cout << std::setw(10) << first << "|";
        std::cout << std::setw(10) << last << "|";
        std::cout << std::setw(10) << nick << "|";
        std::cout << std::endl;
    }

    std::string input;
    int selected;

    std::cout << "\nEnter the index of the contact to display: ";
    std::getline(std::cin, input);

    // Convert string to int and validate
    try {
        selected = std::stoi(input);
        if (selected < 0 || selected >= count) {
            std::cout << "Error: Index out of range. Valid range is 0 to " << (count - 1) << std::endl;
            return;
        }
        displayContact(selected);
    } catch (...) {
        std::cout << "Error: Invalid input. Please enter a valid number." << std::endl;
    }
}

void PhoneBook::displayContact(int i) {
    if (i < 0 || i >= count) {
        std::cout << "Invalid index!" << std::endl;
        return;
    }

    std::cout << "\n=== Contact Details ===" << std::endl;
    std::cout << "First Name: " << contacts[i].getFirstName() << std::endl;
    std::cout << "Last Name: " << contacts[i].getLastName() << std::endl;
    std::cout << "Nickname: " << contacts[i].getNickname() << std::endl;
    std::cout << "Phone Number: " << contacts[i].getPhoneNumber() << std::endl;
    std::cout << "Darkest Secret: " << contacts[i].getDarkestSecret() << std::endl;
    std::cout << "======================" << std::endl;
}