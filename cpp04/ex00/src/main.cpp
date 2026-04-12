#include "ClapTrap.hpp"
#include <iostream>

int main(void)
{
	std::cout << "=== Basic ClapTrap test ===" << std::endl;
	{
		ClapTrap alice("Alice");
		ClapTrap bob("Bob");

		alice.attack("Bob");
		bob.takeDamage(3);
		bob.beRepaired(2);
	}

	std::cout << std::endl << "=== Copy / assignment test ===" << std::endl;
	{
		ClapTrap original("Original");
		original.takeDamage(2);

		ClapTrap copy(original);
		copy.attack("dummy");

		ClapTrap assigned;
		assigned = original;
		assigned.attack("another");
	}

	std::cout << std::endl << "=== Energy exhaustion test ===" << std::endl;
	{
		ClapTrap charlie("Charlie");
		for (int i = 0; i < 11; ++i)
			charlie.attack("practice dummy");
		charlie.beRepaired(1);
	}

	std::cout << std::endl << "=== HP exhaustion test ===" << std::endl;
	{
		ClapTrap dave("Dave");
		dave.takeDamage(100);
		dave.beRepaired(5);
		dave.attack("ghost");
		dave.takeDamage(1);
	}

	std::cout << std::endl << "=== End of tests ===" << std::endl;
	return 0;
}
