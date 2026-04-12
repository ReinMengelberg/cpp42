#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iostream>
#include <string>

using namespace std;

class Contact {
    private:
        string first_name;
        string last_name;
        string nickname;
        string phone_number;
        string darkest_secret;
        
    
    public:
        Contact();
        
        void setFirstName(const string& input);
        void setLastName(const string& input);
        void setNickname(const string& input);
        void setPhoneNumber(const string& input);
        void setDarkestSecret(const string& input);
        
        string getFirstName(void) const;
        string getLastName(void) const;
        string getNickname(void) const;
        string getPhoneNumber(void) const;
        string getDarkestSecret(void) const;
};

#endif