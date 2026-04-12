#include "../includes/Zombie.hpp"

int main() {
    Zombie z1;
    z1.announce();

    Zombie z2;
    z2.setName("Karel");
    z2.announce();

    Zombie* zombie3 = newZombie("Sjaak");
    zombie3->announce();
    delete zombie3;

    randomChump("Jamiro");

    return 0;
}