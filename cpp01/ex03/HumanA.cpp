// ./HumanA.cpp
#include "HumanA.hpp"
#include <iostream>

HumanA::HumanA(std::string name, Weapon &weapon) {
    this->name = name;
	this->weapon = &weapon;
}

HumanA::~HumanA(void) {}

std::string HumanA::getName(void) const {
    return name;
}

void HumanA::setName(const std::string& name) {
    this->name = name;
}

Weapon *HumanA::getWeapon(void) {
	return this->weapon;
}

void HumanA::setWeapon(Weapon &weapon) {
    this->weapon = &weapon;
}

void HumanA::attack(void) {
	if (this->weapon) {
		std::cout << this->name << " attacks with their " << this->weapon->getType() << std::endl;
	} else {
		std::cout << this->name << " attacks with their bare hands" << std::endl;
	}
}