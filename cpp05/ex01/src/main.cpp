#include "Bureaucrat.hpp"
#include "Form.hpp"

int main(void)
{
	std::cout << "=== Test: form construction and printing ===" << std::endl;
	{
		Form taxes("Tax Return 28B", 50, 25);

		std::cout << taxes << std::endl;
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
		Bureaucrat boss("Vogon Prostetnic", 20);
		Form taxes("Tax Return 28B", 50, 25);

		boss.signForm(taxes);
		std::cout << taxes << std::endl;
	}

	std::cout << std::endl << "=== Test: a bureaucrat whose grade is too low ===" << std::endl;
	{
		Bureaucrat intern("Arthur Dent", 100);
		Form taxes("Tax Return 28B", 50, 25);

		intern.signForm(taxes);
		std::cout << taxes << std::endl;
	}

	std::cout << std::endl << "=== Test: signing exactly at the required grade ===" << std::endl;
	{
		Bureaucrat clerk("Ford Prefect", 50);
		Form taxes("Tax Return 28B", 50, 25);

		clerk.signForm(taxes);
		std::cout << taxes << std::endl;
	}

	std::cout << std::endl << "=== Test: beSigned() throws when called directly ===" << std::endl;
	{
		Bureaucrat intern("Marvin", 150);
		Form secret("Top Secret", 1, 1);

		try
		{
			secret.beSigned(intern);
		}
		catch (std::exception& e)
		{
			std::cout << "Caught: " << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== End of tests ===" << std::endl;
	return 0;
}
