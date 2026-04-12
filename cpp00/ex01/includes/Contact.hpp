#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iostream>
#include <string>

class Contact {
    private:
        std::string first_name;
        std::string last_name;
        std::string nickname;
        std::string phone_number;
        std::string darkest_secret;


    public:
        Contact();

        void setFirstName(const std::string& input);
        void setLastName(const std::string& input);
        void setNickname(const std::string& input);
        void setPhoneNumber(const std::string& input);
        void setDarkestSecret(const std::string& input);

        std::string getFirstName(void) const;
        std::string getLastName(void) const;
        std::string getNickname(void) const;
        std::string getPhoneNumber(void) const;
        std::string getDarkestSecret(void) const;
};

#endif