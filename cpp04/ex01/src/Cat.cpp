#include "Cat.hpp"
#include "Brain.hpp"
#include <iostream>

Cat::Cat() : Animal("Cat"), brain(new Brain())
{
	std::cout << "Cat default constructor called." << std::endl;
}

Cat::Cat(const Cat& other) : Animal(other), brain(new Brain(*other.brain))
{
	std::cout << "Cat copy constructor called (deep copy)." << std::endl;
}

Cat& Cat::operator=(const Cat& other)
{
	std::cout << "Cat copy assignment called (deep copy)." << std::endl;
	if (this != &other)
	{
		Animal::operator=(other);
		delete brain;
		brain = new Brain(*other.brain);
	}
	return *this;
}

Cat::~Cat()
{
	std::cout << "Cat destructor called." << std::endl;
	delete brain;
}

void Cat::makeSound() const
{
	std::cout << type << " makes sound: " << "Purrrrrr Purr Purrr!" << std::endl;
}

Brain* Cat::getBrain() const
{
	return brain;
}
