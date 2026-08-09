#include "Animal.hpp"
#include <iostream>

Animal::Animal() : type("Animal")
{
	std::cout << "Animal default constructor called." << std::endl;
}

Animal::Animal(const std::string& type) : type(type)
{
	std::cout << "Animal type constructor called for " << type << "." << std::endl;
}

Animal::Animal(const Animal& other) : type(other.type)
{
	std::cout << "Animal copy constructor called for " << type << "." << std::endl;
}

Animal& Animal::operator=(const Animal& other)
{
	std::cout << "Animal copy assignment called: " << type << " = " << other.type << "." << std::endl;
	if (this != &other)
		type = other.type;
	return *this;
}

Animal::~Animal()
{
	std::cout << "Animal destructor called for " << type << "." << std::endl;
}

void Animal::makeSound() const
{
	std::cout << type << " makes sound: " << "**Generic Animal Sound**" << std::endl;
}

const std::string& Animal::getType() const
{
	return type;
}
