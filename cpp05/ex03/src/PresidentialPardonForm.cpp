#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm()
	: AForm("PresidentialPardonForm", 25, 5), target("someone")
{
	std::cout << "PresidentialPardonForm default constructor called for " << target << "." << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const std::string& target)
	: AForm("PresidentialPardonForm", 25, 5), target(target)
{
	std::cout << "PresidentialPardonForm constructor called for " << target << "." << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& other)
	: AForm(other), target(other.target)
{
	std::cout << "PresidentialPardonForm copy constructor called for " << target << "." << std::endl;
}

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& other)
{
	std::cout << "PresidentialPardonForm copy assignment called for " << target << "." << std::endl;
	if (this != &other)
	{
		AForm::operator=(other);
		target = other.target;
	}
	return *this;
}

PresidentialPardonForm::~PresidentialPardonForm()
{
	std::cout << "PresidentialPardonForm destructor called for " << target << "." << std::endl;
}

const std::string& PresidentialPardonForm::getTarget() const
{
	return target;
}

void PresidentialPardonForm::action() const
{
	std::cout << target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}
