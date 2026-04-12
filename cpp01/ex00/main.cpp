#include "Zombie.hpp"

int main() {
    // Using the default constructor and announce method
    Zombie z1;
    z1.announce();

    // Using the setName method and announce method
    Zombie z2;
    z2.setName("Zombie2");
    z2.announce();

    // Using the newZombie function from Util.cpp
    Zombie* zombie3 = newZombie("Zombie3");
    zombie3->announce();
    delete zombie3; // Don't forget to delete the allocated memory

    // Using the randomChump function from Util.cpp
    randomChump("Zombie4");

    return 0;
}