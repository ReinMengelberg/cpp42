// ./Weapon.cpp
#include "Weapon.hpp"
#include <iostream>

Weapon::Weapon(std::string type) {
    this->type = type;
}

Weapon::~Weapon(void) {}

const std::string &Weapon::getType(void) const {
    return type;
}

void Weapon::setType(const std::string& type) {
    this->type = type;
}