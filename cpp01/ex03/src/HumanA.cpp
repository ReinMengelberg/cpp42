// ./HumanA.cpp
#include "HumanA.hpp"
#include <iostream>

HumanA::HumanA(std::string name, Weapon &weapon) : name(name), weapon(weapon) {}

HumanA::~HumanA(void) {}

std::string HumanA::getName(void) const {
    return name;
}

void HumanA::setName(const std::string& name) {
    this->name = name;
}

void HumanA::attack(void) {
	std::cout << this->name << " attacks with their " << this->weapon.getType() << std::endl;
}