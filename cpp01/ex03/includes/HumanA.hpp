// ./HumanA.hpp
#ifndef HUMANA_HPP
#define HUMANA_HPP
#include "Weapon.hpp"
#include <iostream>
#include <string>

class HumanA {
	public: 
		HumanA(std::string name, Weapon &weapon); // Constructor
		~HumanA(void); // Destructor

		std::string getName(void) const;
		void setName(const std::string &name);

		void setWeapon(Weapon &Weapon);
		Weapon *getWeapon(void);

		void attack(void);

	private:
		std::string name;
		Weapon *weapon;
};

#endif