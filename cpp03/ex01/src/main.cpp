#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>

int main(void)
{
	std::cout << "=== ClapTrap basic test ===" << std::endl;
	{
		ClapTrap sjaak("Sjaak");
		sjaak.attack("pinata");
		sjaak.takeDamage(4);
		sjaak.beRepaired(2);
	}

	std::cout << std::endl << "=== ScavTrap construction chaining ===" << std::endl;
	{
		ScavTrap henk("Henk");
		henk.attack("bokszak");
		henk.takeDamage(30);
		henk.beRepaired(10);
		henk.guardGate();
	}

	std::cout << std::endl << "=== ScavTrap copy / assignment ===" << std::endl;
	{
		ScavTrap pieter("Pieter");
		pieter.takeDamage(15);

		ScavTrap copy(pieter);
		copy.attack("trainingspop");

		ScavTrap assigned;
		assigned = pieter;
		assigned.guardGate();
	}

	std::cout << std::endl << "=== Polymorphic slicing via base pointer ===" << std::endl;
	{
		// attack() is not virtual, so through a ClapTrap* pointer
		// the base-class version is called — this shows the static binding
		// behaviour you typically get in C++98 without virtual functions.
		ClapTrap* ptr = new ScavTrap("Gerrit");
		ptr->attack("vogelverschrikker");
		delete ptr;
	}

	std::cout << std::endl << "=== ScavTrap energy exhaustion ===" << std::endl;
	{
		ScavTrap bertus("Bertus");
		for (int i = 0; i < 51; ++i)
			bertus.attack("zandzak");
	}

	std::cout << std::endl << "=== End of tests ===" << std::endl;
	return 0;
}
