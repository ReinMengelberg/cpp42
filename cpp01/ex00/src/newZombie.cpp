#include "Zombie.hpp"

Zombie* newZombie(const std::string& name) {
    Zombie* zombie = new Zombie();
    zombie->setName(name);
    return zombie;
}
