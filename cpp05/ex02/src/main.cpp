#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

#include <cstdlib>
#include <ctime>

int main(void)
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	// AForm is abstract: `AForm f("a", 1, 1);` would not compile.

	std::cout << "=== Test: shrubbery creation (sign 145, exec 137) ===" << std::endl;
	{
		Bureaucrat				gardener("Ford Prefect", 137);
		ShrubberyCreationForm	form("home");

		std::cout << form << std::endl;
		gardener.signForm(form);
		gardener.executeForm(form);
	}

	std::cout << std::endl << "=== Test: executing an unsigned form ===" << std::endl;
	{
		Bureaucrat			boss("Vogon Prostetnic", 1);
		RobotomyRequestForm	form("Bender");

		boss.executeForm(form);
	}

	std::cout << std::endl << "=== Test: robotomy (sign 72, exec 45), 50% success ===" << std::endl;
	{
		Bureaucrat			boss("Vogon Prostetnic", 45);
		RobotomyRequestForm	form("Bender");

		boss.signForm(form);
		for (int i = 0; i < 4; i++)
			boss.executeForm(form);
	}

	std::cout << std::endl << "=== Test: grade too low to execute ===" << std::endl;
	{
		Bureaucrat				clerk("Arthur Dent", 30);
		PresidentialPardonForm	form("Arthur Dent");

		clerk.signForm(form);
		clerk.executeForm(form);
	}

	std::cout << std::endl << "=== Test: presidential pardon (sign 25, exec 5) ===" << std::endl;
	{
		Bureaucrat				president("Zaphod Beeblebrox", 1);
		PresidentialPardonForm	form("Arthur Dent");

		president.signForm(form);
		president.executeForm(form);
	}

	std::cout << std::endl << "=== Test: polymorphic use through AForm* ===" << std::endl;
	{
		Bureaucrat	boss("Trillian", 1);
		AForm*		forms[3];

		forms[0] = new ShrubberyCreationForm("garden");
		forms[1] = new RobotomyRequestForm("Marvin");
		forms[2] = new PresidentialPardonForm("Slartibartfast");

		for (int i = 0; i < 3; i++)
		{
			std::cout << *forms[i] << std::endl;
			boss.signForm(*forms[i]);
			boss.executeForm(*forms[i]);
			delete forms[i];
		}
	}

	std::cout << std::endl << "=== Test: execute() throws when called directly ===" << std::endl;
	{
		Bureaucrat				intern("Marvin", 150);
		PresidentialPardonForm	form("Marvin");

		try
		{
			form.execute(intern);
		}
		catch (std::exception& e)
		{
			std::cout << "Caught: " << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== End of tests ===" << std::endl;
	return 0;
}
