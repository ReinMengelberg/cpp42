#include "Bureaucrat.hpp"
#include "Form.hpp"

int main(void)
{
	std::cout << "=== Test: form construction and printing ===" << std::endl;
	{
		Form delivery("Planet Express Delivery Form", 50, 25);

		std::cout << delivery << std::endl;
	}

	std::cout << std::endl << "=== Test: invalid form grades ===" << std::endl;
	try
	{
		Form impossible("Impossible", 0, 10);
		std::cout << impossible << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Caught: " << e.what() << std::endl;
	}
	try
	{
		Form impossible("Impossible", 10, 151);
		std::cout << impossible << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Caught: " << e.what() << std::endl;
	}

	std::cout << std::endl << "=== Test: a bureaucrat with a high enough grade signs ===" << std::endl;
	{
		Bureaucrat boss("Morgan Proctor", 20);
		Form delivery("Planet Express Delivery Form", 50, 25);

		boss.signForm(delivery);
		std::cout << delivery << std::endl;
	}

	std::cout << std::endl << "=== Test: a bureaucrat whose grade is too low ===" << std::endl;
	{
		Bureaucrat intern("Philip J. Fry", 100);
		Form delivery("Planet Express Delivery Form", 50, 25);

		intern.signForm(delivery);
		std::cout << delivery << std::endl;
	}

	std::cout << std::endl << "=== Test: signing exactly at the required grade ===" << std::endl;
	{
		Bureaucrat exactGrade("Hermes Conrad", 50);
		Form delivery("Planet Express Delivery Form", 50, 25);

		exactGrade.signForm(delivery);
		std::cout << delivery << std::endl;
	}

	std::cout << std::endl << "=== Test: beSigned() throws when called directly ===" << std::endl;
	{
		Bureaucrat janitor("Scruffy", 150);
		Form secret("DOOP Clearance", 1, 1);

		try
		{
			secret.beSigned(janitor);
		}
		catch (std::exception& e)
		{
			std::cout << "Caught: " << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== End of tests ===" << std::endl;
	return 0;
}
