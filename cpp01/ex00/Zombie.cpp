// ./Zombie.cpp
#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie(void) {
    // Constructor implementation
    name = "DefaultZombie";
}

Zombie::~Zombie(void) {
    // Destructor implementation
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