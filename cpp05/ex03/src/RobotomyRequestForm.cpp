#include "RobotomyRequestForm.hpp"

#include <cstdlib>

RobotomyRequestForm::RobotomyRequestForm()
	: AForm("RobotomyRequestForm", 72, 45), target("someone")
{
	std::cout << "RobotomyRequestForm default constructor called for " << target << "." << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
	: AForm("RobotomyRequestForm", 72, 45), target(target)
{
	std::cout << "RobotomyRequestForm constructor called for " << target << "." << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other)
	: AForm(other), target(other.target)
{
	std::cout << "RobotomyRequestForm copy constructor called for " << target << "." << std::endl;
}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& other)
{
	std::cout << "RobotomyRequestForm copy assignment called for " << target << "." << std::endl;
	if (this != &other)
	{
		AForm::operator=(other);
		target = other.target;
	}
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm()
{
	std::cout << "RobotomyRequestForm destructor called for " << target << "." << std::endl;
}

const std::string& RobotomyRequestForm::getTarget() const
{
	return target;
}

void RobotomyRequestForm::action() const
{
	std::cout << "* BZZZZZZT... DRRRRRRRR... drilling noises *" << std::endl;
	if (std::rand() % 2 == 0)
		std::cout << target << " has been robotomized successfully." << std::endl;
	else
		std::cout << "The robotomy of " << target << " failed." << std::endl;
}
