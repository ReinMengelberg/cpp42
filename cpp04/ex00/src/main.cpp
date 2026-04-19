#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

int main(void)
{
	std::cout << "=== Test: polymorphic dispatch ===" << std::endl;
	{
		const Animal* meta = new Animal();
		const Animal* sjakie = new Dog();
		const Animal* mittens = new Cat();

		std::cout << "sjakie type: " << sjakie->getType() << std::endl;
		std::cout << "mittens type: " << mittens->getType() << std::endl;

		mittens->makeSound();
		sjakie->makeSound();
		meta->makeSound();

		delete meta;
		delete sjakie;
		delete mittens;
	}

	std::cout << std::endl << "=== Test: Stack instances ===" << std::endl;
	{
		Dog georgie;
		Cat leopold;
		georgie.makeSound();
		leopold.makeSound();
	}

	std::cout << std::endl << "=== Test: copy constucting & copy assignment on dog ===" << std::endl;
	{
		Dog original;
		Dog copy(original);
		Dog assigned;
		assigned = original;
		copy.makeSound();
		assigned.makeSound();
	}

	std::cout << std::endl << "=== Test: WrongAnimal ===" << std::endl;
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
