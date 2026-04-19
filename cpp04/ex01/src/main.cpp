#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"
#include <iostream>

#define HERD_SIZE 10

int main(void)
{
	std::cout << "=== Test: no-leak polymorphic delete ===" << std::endl;
	{
		const Animal* sjakie = new Dog();
		const Animal* mittens = new Cat();

		sjakie->makeSound();
		mittens->makeSound();

		delete sjakie;
		delete mittens;
	}

	std::cout << std::endl << "=== Test: Array of Animals (half Dog, half Cat) ===" << std::endl;
	{
		Animal* herd[HERD_SIZE];

		for (int i = 0; i < HERD_SIZE / 2; i++)
			herd[i] = new Dog();
		for (int i = HERD_SIZE / 2; i < HERD_SIZE; i++)
			herd[i] = new Cat();

		std::cout << std::endl << "-- making sounds --" << std::endl;
		for (int i = 0; i < HERD_SIZE; i++)
			herd[i]->makeSound();

		std::cout << std::endl << "-- deleting herd --" << std::endl;
		for (int i = 0; i < HERD_SIZE; i++)
			delete herd[i];
	}

	std::cout << std::endl << "=== Test: Deep copy check: Dog ===" << std::endl;
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

	std::cout << std::endl << "=== Test: Deep copy check: Cat via assignment ===" << std::endl;
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
