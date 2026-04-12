#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>

int main(void)
{
	std::cout << "=== ClapTrap basic test ===" << std::endl;
	{
		ClapTrap alice("Alice");
		alice.attack("target");
		alice.takeDamage(4);
		alice.beRepaired(2);
	}

	std::cout << std::endl << "=== ScavTrap construction chaining ===" << std::endl;
	{
		ScavTrap sentinel("Sentinel");
		sentinel.attack("intruder");
		sentinel.takeDamage(30);
		sentinel.beRepaired(10);
		sentinel.guardGate();
	}

	std::cout << std::endl << "=== ScavTrap copy / assignment ===" << std::endl;
	{
		ScavTrap original("Original");
		original.takeDamage(15);

		ScavTrap copy(original);
		copy.attack("clone target");

		ScavTrap assigned;
		assigned = original;
		assigned.guardGate();
	}

	std::cout << std::endl << "=== Polymorphic slicing via base pointer ===" << std::endl;
	{
		// attack() is not virtual, so through a ClapTrap* pointer
		// the base-class version is called — this shows the static binding
		// behaviour you typically get in C++98 without virtual functions.
		ClapTrap* ptr = new ScavTrap("Polybot");
		ptr->attack("victim");
		delete ptr;
	}

	std::cout << std::endl << "=== ScavTrap energy exhaustion ===" << std::endl;
	{
		ScavTrap drained("Drained");
		for (int i = 0; i < 51; ++i)
			drained.attack("dummy");
	}

	std::cout << std::endl << "=== End of tests ===" << std::endl;
	return 0;
}
