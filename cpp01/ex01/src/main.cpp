#include "Zombie.hpp"

int main(void) {
	Zombie *horde1;
    Zombie *horde2;

	std::string name1 = "Klaas";
    horde1 = zombieHorde(10, name1);

    for (int i = 0; i < 10; i++) {
        horde1[i].announce();
    }

    delete[] horde1;

	std::string name2 = "Sjaak";
    horde2 = zombieHorde(5, name2);

    for (int i = 0; i < 5; i++) {
        horde2[i].announce();
    }

    delete[] horde2;

    return 0;
}