// ./Weapon.cpp
#include "Weapon.hpp"
#include <iostream>

Weapon::Weapon(std::string type) {
    this->type = type;
}

Weapon::~Weapon(void) {}

std::string Weapon::getType(void) const {
    return type;
}

void Weapon::setType(const std::string& type) {
    this->type = type;
}