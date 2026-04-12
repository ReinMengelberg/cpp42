#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include <iostream>

int main(void)
{
	std::cout << "=== ClapTrap baseline ===" << std::endl;
	{
		ClapTrap alice("Alice");
		alice.attack("target");
		alice.takeDamage(4);
		alice.beRepaired(2);
	}

	std::cout << std::endl << "=== ScavTrap test ===" << std::endl;
	{
		ScavTrap sentinel("Sentinel");
		sentinel.attack("intruder");
		sentinel.takeDamage(30);
		sentinel.beRepaired(10);
		sentinel.guardGate();
	}

	std::cout << std::endl << "=== FragTrap construction chaining ===" << std::endl;
	{
		FragTrap party("Party");
		party.attack("boss");
		party.takeDamage(25);
		party.beRepaired(10);
		party.highFivesGuys();
	}

	std::cout << std::endl << "=== FragTrap copy / assignment ===" << std::endl;
	{
		FragTrap original("Original");
		original.takeDamage(20);

		FragTrap copy(original);
		copy.attack("clone target");
		copy.highFivesGuys();

		FragTrap assigned;
		assigned = original;
		assigned.highFivesGuys();
	}

	std::cout << std::endl << "=== Side-by-side derived classes ===" << std::endl;
	{
		ScavTrap scav("Guardian");
		FragTrap frag("Partier");

		scav.attack("invader");
		frag.attack("invader");

		scav.guardGate();
		frag.highFivesGuys();
	}

	std::cout << std::endl << "=== End of tests ===" << std::endl;
	return 0;
}
