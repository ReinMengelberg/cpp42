#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

int main(void)
{
	std::cout << "=== Subject example: polymorphic dispatch ===" << std::endl;
	{
		const Animal* meta = new Animal();
		const Animal* j = new Dog();
		const Animal* i = new Cat();

		std::cout << "j type: " << j->getType() << std::endl;
		std::cout << "i type: " << i->getType() << std::endl;

		i->makeSound();
		j->makeSound();
		meta->makeSound();

		delete meta;
		delete j;
		delete i;
	}

	std::cout << std::endl << "=== Stack instances ===" << std::endl;
	{
		Dog rex;
		Cat whiskers;
		rex.makeSound();
		whiskers.makeSound();
	}

	std::cout << std::endl << "=== Copy semantics on Dog ===" << std::endl;
	{
		Dog original;
		Dog copy(original);
		Dog assigned;
		assigned = original;
		copy.makeSound();
		assigned.makeSound();
	}

	std::cout << std::endl << "=== WrongAnimal: no virtual dispatch ===" << std::endl;
	{
		const WrongAnimal* meta = new WrongAnimal();
		const WrongAnimal* i = new WrongCat();

		std::cout << "i type: " << i->getType() << std::endl;

		i->makeSound();
		meta->makeSound();

		WrongCat concrete;
		concrete.makeSound();

		delete meta;
		delete i;
	}

	std::cout << std::endl << "=== End of tests ===" << std::endl;
	return 0;
}
