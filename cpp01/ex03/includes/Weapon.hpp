// ./Weapon.hpp
#ifndef WEAPON_HPP
#define WEAPON_HPP
#include <iostream>
#include <string>

class Weapon {
	public: 
		Weapon(std::string type);
		~Weapon(void);

		std::string getType(void) const;
		void setType(const std::string &type);

	private:
		std::string type;
};

#endif