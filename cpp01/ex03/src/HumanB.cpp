// ./HumanB.cpp
#include "HumanB.hpp"
#include <iostream>

HumanB::HumanB(std::string name) {
    this->name = name;
    this->weapon = NULL;
}

HumanB::~HumanB(void) {}

std::string HumanB::getName(void) const {
    return name;
}

void HumanB::setName(const std::string& name) {
    this->name = name;
}

Weapon *HumanB::getWeapon(void) {
	return this->weapon;
}

void HumanB::setWeapon(Weapon &weapon) {
    this->weapon = &weapon;
}

void HumanB::attack(void) {
	if (this->weapon) {
		std::cout << this->name << " attacks with their " << this->weapon->getType() << std::endl;
	} else {
		std::cout << this->name << " attacks with their bare hands" << std::endl;
	}
}