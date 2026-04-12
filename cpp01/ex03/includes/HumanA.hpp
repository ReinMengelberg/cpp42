// ./HumanA.hpp
#ifndef HUMANA_HPP
#define HUMANA_HPP
#include "Weapon.hpp"
#include <iostream>
#include <string>

class HumanA {
	public:
		HumanA(std::string name, Weapon &weapon);
		~HumanA(void);

		std::string getName(void) const;
		void setName(const std::string &name);

		void attack(void);

	private:
		std::string name;
		Weapon &weapon;
};

#endif