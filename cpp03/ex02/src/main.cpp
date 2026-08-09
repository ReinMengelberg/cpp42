#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include <iostream>

int main(void)
{
	std::cout << "=== ClapTrap baseline ===" << std::endl;
	{
		ClapTrap sjaak("Sjaak");
		sjaak.attack("pinata");
		sjaak.takeDamage(4);
		sjaak.beRepaired(2);
	}

	std::cout << std::endl << "=== ScavTrap test ===" << std::endl;
	{
		ScavTrap henk("Henk");
		henk.attack("bokszak");
		henk.takeDamage(30);
		henk.beRepaired(10);
		henk.guardGate();
	}

	std::cout << std::endl << "=== FragTrap construction chaining ===" << std::endl;
	{
		FragTrap wim("Wim");
		wim.attack("stropop");
		wim.takeDamage(25);
		wim.beRepaired(10);
		wim.highFivesGuys();
	}

	std::cout << std::endl << "=== FragTrap copy / assignment ===" << std::endl;
	{
		FragTrap pieter("Pieter");
		pieter.takeDamage(20);

		FragTrap copy(pieter);
		copy.attack("trainingspop");
		copy.highFivesGuys();

		FragTrap assigned;
		assigned = pieter;
		assigned.highFivesGuys();
	}

	std::cout << std::endl << "=== Side-by-side derived classes ===" << std::endl;
	{
		ScavTrap dirk("Dirk");
		FragTrap jaap("Jaap");

		dirk.attack("vogelverschrikker");
		jaap.attack("vogelverschrikker");

		dirk.guardGate();
		jaap.highFivesGuys();
	}

	std::cout << std::endl << "=== End of tests ===" << std::endl;
	return 0;
}
