#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie(void) {
    name = "Unknown";
}

Zombie::~Zombie(void) {
    std::cout << name << " has been destroyed!" << std::endl;
}

void Zombie::announce(void) {
    std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

std::string Zombie::getName(void) const {
    return name;
}

void Zombie::setName(const std::string& name) {
    this->name = name;
}