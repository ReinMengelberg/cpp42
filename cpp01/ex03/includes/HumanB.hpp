// ./HumanB.hpp
#ifndef HUMANB_HPP
#define HUMANB_HPP
#include "Weapon.hpp"
#include <iostream>
#include <string>

class HumanB {
	public: 
		HumanB(std::string name); // Constructor
		~HumanB(void); // Destructor

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