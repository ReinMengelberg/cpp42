#include "ClapTrap.hpp"
#include <iostream>

int main(void)
{
	std::cout << "=== Basic ClapTrap test ===" << std::endl;
	{
		ClapTrap sjaak("Sjaak");
		ClapTrap karel("Karel");

		sjaak.attack("Karel");
		karel.takeDamage(3);
		karel.beRepaired(2);
	}

	std::cout << std::endl << "=== Copy / assignment test ===" << std::endl;
	{
		ClapTrap pieter("Pieter");
		pieter.takeDamage(2);

		ClapTrap copy(pieter);
		copy.attack("pinata");

		ClapTrap assigned;
		assigned = pieter;
		assigned.attack("bokszak");
	}

	std::cout << std::endl << "=== Energy exhaustion test ===" << std::endl;
	{
		ClapTrap henk("Henk");
		for (int i = 0; i < 11; ++i)
			henk.attack("oefenpop");
		henk.beRepaired(1);
	}

	std::cout << std::endl << "=== HP exhaustion test ===" << std::endl;
	{
		ClapTrap kees("Kees");
		kees.takeDamage(100);
		kees.beRepaired(5);
		kees.attack("stropop");
		kees.takeDamage(1);
	}

	std::cout << std::endl << "=== End of tests ===" << std::endl;
	return 0;
}
