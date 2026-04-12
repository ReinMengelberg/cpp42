#include "Contact.hpp"

Contact::Contact() {
    first_name = "";
    last_name = "";
    nickname = "";
    phone_number = "";
    darkest_secret = "";
}

void Contact::setFirstName(const std::string &input) {
    first_name = input;
}

void Contact::setLastName(const std::string &input) {
    last_name = input;
}

void Contact::setNickname(const std::string &input) {
    nickname = input;
}

void Contact::setPhoneNumber(const std::string &input) {
    phone_number = input;
}

void Contact::setDarkestSecret(const std::string &input) {
    darkest_secret = input;
}

std::string Contact::getFirstName(void) const {
    return first_name;
}

std::string Contact::getLastName(void) const {
    return last_name;
}

std::string Contact::getNickname(void) const {
    return nickname;
}

std::string Contact::getPhoneNumber(void) const {
    return phone_number;
}

std::string Contact::getDarkestSecret(void) const {
    return darkest_secret;
}