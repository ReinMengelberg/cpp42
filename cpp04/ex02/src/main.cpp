#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"
#include <iostream>

#define HERD_SIZE 10

int main(void)
{
	// Animal is now abstract: `Animal a;` or `new Animal()` would not compile.
	// Uncomment to verify:
	// Animal a;
	// Animal* a = new Animal();

	std::cout << "=== Test: Polymorphic dispatch via abstract Animal* ===" << std::endl;
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

	std::cout << std::endl << "=== Test: Deep copy still intact ===" << std::endl;
	{
		Dog original;
		original.getBrain()->setIdea(0, "Chase the mailman");

		Dog copy(original);
		copy.getBrain()->setIdea(0, "Steal bacon");

		std::cout << "original idea[0]: " << original.getBrain()->getIdea(0) << std::endl;
		std::cout << "copy     idea[0]: " << copy.getBrain()->getIdea(0) << std::endl;

		if (original.getBrain() != copy.getBrain())
			std::cout << "Success: brain pointers differ -> deep copy" << std::endl;
		else
			std::cout << "Error: shallow copy detected!" << std::endl;
	}

	std::cout << std::endl << "=== End of tests ===" << std::endl;
	return 0;
}
