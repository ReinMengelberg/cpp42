#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"
#include <iostream>

#define HERD_SIZE 10

int main(void)
{
	std::cout << "=== Subject example: no-leak polymorphic delete ===" << std::endl;
	{
		const Animal* j = new Dog();
		const Animal* i = new Cat();

		j->makeSound();
		i->makeSound();

		delete j;
		delete i;
	}

	std::cout << std::endl << "=== Array of Animals (half Dog, half Cat) ===" << std::endl;
	{
		Animal* herd[HERD_SIZE];

		for (int k = 0; k < HERD_SIZE / 2; k++)
			herd[k] = new Dog();
		for (int k = HERD_SIZE / 2; k < HERD_SIZE; k++)
			herd[k] = new Cat();

		std::cout << std::endl << "-- making sounds --" << std::endl;
		for (int k = 0; k < HERD_SIZE; k++)
			herd[k]->makeSound();

		std::cout << std::endl << "-- deleting herd --" << std::endl;
		for (int k = 0; k < HERD_SIZE; k++)
			delete herd[k];
	}

	std::cout << std::endl << "=== Deep copy check: Dog ===" << std::endl;
	{
		Dog original;
		original.getBrain()->setIdea(0, "Squirrel!");
		original.getBrain()->setIdea(1, "Walkies?");

		Dog copy(original);
		copy.getBrain()->setIdea(0, "Cat on fence");

		std::cout << "original idea[0]: " << original.getBrain()->getIdea(0) << std::endl;
		std::cout << "copy     idea[0]: " << copy.getBrain()->getIdea(0) << std::endl;
		std::cout << "original idea[1]: " << original.getBrain()->getIdea(1) << std::endl;
		std::cout << "copy     idea[1]: " << copy.getBrain()->getIdea(1) << std::endl;

		if (original.getBrain() != copy.getBrain())
			std::cout << "[OK] brain pointers differ -> deep copy" << std::endl;
		else
			std::cout << "[KO] shallow copy detected!" << std::endl;
	}

	std::cout << std::endl << "=== Deep copy check: Cat via assignment ===" << std::endl;
	{
		Cat original;
		original.getBrain()->setIdea(0, "Nap on keyboard");

		Cat assigned;
		assigned = original;
		assigned.getBrain()->setIdea(0, "Knock glass off table");

		std::cout << "original idea[0]: " << original.getBrain()->getIdea(0) << std::endl;
		std::cout << "assigned idea[0]: " << assigned.getBrain()->getIdea(0) << std::endl;

		if (original.getBrain() != assigned.getBrain())
			std::cout << "[OK] brain pointers differ -> deep copy" << std::endl;
		else
			std::cout << "[KO] shallow copy detected!" << std::endl;
	}

	std::cout << std::endl << "=== End of tests ===" << std::endl;
	return 0;
}
