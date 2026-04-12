#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <iostream>
#include <string>
#include <iomanip> 
#include <Contact.hpp>

class PhoneBook {
    private:
        Contact contacts[8];
        int count;
        int index;

    public:
        PhoneBook();
        void addContact();
        void searchContacts();
        void displayContact(int index);
};

#endif