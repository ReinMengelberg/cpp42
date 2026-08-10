#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

// One small builder per form, so makeForm() only has to look up a name in a
// table instead of walking through a chain of if / else if.

static AForm*	makeShrubberyCreationForm(const std::string& target)
{
	return new ShrubberyCreationForm(target);
}

static AForm*	makeRobotomyRequestForm(const std::string& target)
{
	return new RobotomyRequestForm(target);
}

static AForm*	makePresidentialPardonForm(const std::string& target)
{
	return new PresidentialPardonForm(target);
}

Intern::Intern()
{
	std::cout << "Intern default constructor called." << std::endl;
}

Intern::Intern(const Intern& other)
{
	(void)other;
	std::cout << "Intern copy constructor called." << std::endl;
}

Intern& Intern::operator=(const Intern& other)
{
	(void)other;
	std::cout << "Intern copy assignment called." << std::endl;
	return *this;
}

Intern::~Intern()
{
	std::cout << "Intern destructor called." << std::endl;
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target) const
{
	typedef AForm*	(*FormBuilder)(const std::string&);

	const std::string	names[3] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};
	const FormBuilder	builders[3] = {
		&makeShrubberyCreationForm,
		&makeRobotomyRequestForm,
		&makePresidentialPardonForm
	};

	for (int i = 0; i < 3; i++)
	{
		if (names[i] == formName)
		{
			std::cout << "Intern creates " << formName << std::endl;
			return builders[i](target);
		}
	}
	std::cerr << "Intern cannot create " << formName
		<< ": no such form exists." << std::endl;
	return NULL;
}
