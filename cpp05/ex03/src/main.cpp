#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Intern.hpp"

#include <cstdlib>
#include <ctime>

int main(void)
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	std::cout << "=== Test: the intern makes every known form ===" << std::endl;
	{
		Intern				someRandomIntern;
		const std::string	names[3] = {
			"shrubbery creation",
			"robotomy request",
			"presidential pardon"
		};

		for (int i = 0; i < 3; i++)
		{
			AForm*	form = someRandomIntern.makeForm(names[i], "Bender");

			if (form)
			{
				std::cout << *form << std::endl;
				delete form;
			}
		}
	}

	std::cout << std::endl << "=== Test: unknown form name ===" << std::endl;
	{
		Intern	someRandomIntern;
		AForm*	form = someRandomIntern.makeForm("coffee making", "Bender");

		if (!form)
			std::cout << "makeForm() returned NULL, nothing to delete." << std::endl;
		delete form;
	}

	std::cout << std::endl << "=== Test: a form made by the intern gets signed and executed ===" << std::endl;
	{
		Intern		someRandomIntern;
		Bureaucrat	boss("Richard Nixon's Head", 1);
		AForm*		rrf = someRandomIntern.makeForm("robotomy request", "Bender");

		if (rrf)
		{
			boss.signForm(*rrf);
			boss.executeForm(*rrf);
			delete rrf;
		}
	}

	std::cout << std::endl << "=== Test: the intern's shrubbery form gets executed ===" << std::endl;
	{
		Intern		someRandomIntern;
		Bureaucrat	gardener("Hermes Conrad", 1);
		AForm*		scf = someRandomIntern.makeForm("shrubbery creation", "garden");

		if (scf)
		{
			gardener.signForm(*scf);
			gardener.executeForm(*scf);
			delete scf;
		}
	}

	std::cout << std::endl << "=== Test: the intern's form still enforces the grades ===" << std::endl;
	{
		Intern		someRandomIntern;
		Bureaucrat	underqualified("Dr. John Zoidberg", 150);
		AForm*		ppf = someRandomIntern.makeForm("presidential pardon", "Dr. John Zoidberg");

		if (ppf)
		{
			underqualified.signForm(*ppf);
			underqualified.executeForm(*ppf);
			delete ppf;
		}
	}

	std::cout << std::endl << "=== End of tests ===" << std::endl;
	return 0;
}
