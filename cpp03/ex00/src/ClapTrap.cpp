#include "ClapTrap.hpp"
#include <iostream>

ClapTrap::ClapTrap()
	: name("default"), hitPoints(10), energyPoints(10), attackDamage(0)
{
	std::cout << "ClapTrap " << name << " constucted with default constructor." << std::endl;
}

ClapTrap::ClapTrap(const std::string& name)
	: name(name), hitPoints(10), energyPoints(10), attackDamage(0)
{
	std::cout << "ClapTrap " << name << " constucted with name constructor." << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& other)
	: name(other.name),
	  hitPoints(other.hitPoints),
	  energyPoints(other.energyPoints),
	  attackDamage(other.attackDamage)
{
	std::cout << "ClapTrap " << name << " constructed with copy constructor." << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other)
{
	std::cout << "ClapTrap " << name << " copy assigned from " << other.name << "." << std::endl;
	if (this != &other)
	{
		name = other.name;
		hitPoints = other.hitPoints;
		energyPoints = other.energyPoints;
		attackDamage = other.attackDamage;
	}
	return *this;
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap " << name << " destroyed." << std::endl;
}

void ClapTrap::attack(const std::string& target)
{
	if (hitPoints == 0)
	{
		std::cout << "ClapTrap " << name << " can't attack: not enough hitpoints." << std::endl;
		return;
	}
	if (energyPoints == 0)
	{
		std::cout << "ClapTrap " << name << " can't attack: not enough energy points." << std::endl;
		return;
	}
	energyPoints--;
	std::cout << "ClapTrap " << name << " attacks " << target
			  << ", causing " << attackDamage << " points of damage!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	if (hitPoints == 0)
	{
		std::cout << "ClapTrap " << name << " has no hitpoints left." << std::endl;
		return;
	}
	if (amount >= hitPoints)
		hitPoints = 0;
	else
		hitPoints -= amount;
	std::cout << "ClapTrap " << name << " takes " << amount
			  << " points of damage! (" << hitPoints << " HP left)" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (hitPoints == 0)
	{
		std::cout << "ClapTrap " << name << " can't be repaired: is already out of hitpoints" << std::endl;
		return;
	}
	if (energyPoints == 0)
	{
		std::cout << "ClapTrap " << name << " can't be repaired: is already out of energy points" << std::endl;
		return;
	}
	energyPoints--;
	hitPoints += amount;
	std::cout << "ClapTrap " << name << " is repaired for " << amount
			  << " hit points. (" << hitPoints << " HP)" << std::endl;
}
