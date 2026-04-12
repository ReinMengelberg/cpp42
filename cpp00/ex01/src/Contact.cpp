#include "Contact.hpp"

Contact::Contact() {
    first_name = "";
    last_name = "";
    nickname = "";
    phone_number = "";
    darkest_secret = "";
}

void Contact::setFirstName(const string &input) {
    first_name = input;
}

void Contact::setLastName(const string &input) {
    last_name = input;
}

void Contact::setNickname(const string &input) {
    nickname = input;
}

void Contact::setPhoneNumber(const string &input) {
    phone_number = input;
}

void Contact::setDarkestSecret(const string &input) {
    darkest_secret = input;
}

string Contact::getFirstName(void) const {
    return first_name;
}

string Contact::getLastName(void) const {
    return last_name;
}

string Contact::getNickname(void) const {
    return nickname;
}

string Contact::getPhoneNumber(void) const {
    return phone_number;
}

string Contact::getDarkestSecret(void) const {
    return darkest_secret;
}