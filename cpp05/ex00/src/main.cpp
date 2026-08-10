#include "Bureaucrat.hpp"

int main(void)
{
	std::cout << "=== Test: valid bureaucrats ===" << std::endl;
	{
		Bureaucrat boss("Number 1.0", 1);
		Bureaucrat intern("Dr. John Zoidberg", 150);

		std::cout << boss << std::endl;
		std::cout << intern << std::endl;
	}

	std::cout << std::endl << "=== Test: grade too high at construction ===" << std::endl;
	try
	{
		Bureaucrat overachiever("Morgan Proctor", 0);
		std::cout << overachiever << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Caught: " << e.what() << std::endl;
	}

	std::cout << std::endl << "=== Test: grade too low at construction ===" << std::endl;
	try
	{
		Bureaucrat slacker("Philip J. Fry", 151);
		std::cout << slacker << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Caught: " << e.what() << std::endl;
	}

	std::cout << std::endl << "=== Test: increment / decrement ===" << std::endl;
	{
		Bureaucrat mover("Hermes Conrad", 3);

		std::cout << mover << std::endl;
		mover.incrementGrade();
		std::cout << "after increment: " << mover << std::endl;
		mover.decrementGrade();
		mover.decrementGrade();
		std::cout << "after two decrements: " << mover << std::endl;
	}

	std::cout << std::endl << "=== Test: increment past grade 1 ===" << std::endl;
	{
		Bureaucrat top("Mom", 1);

		try
		{
			top.incrementGrade();
		}
		catch (std::exception& e)
		{
			std::cout << "Caught: " << e.what() << std::endl;
		}
		std::cout << "unchanged: " << top << std::endl;
	}

	std::cout << std::endl << "=== Test: decrement past grade 150 ===" << std::endl;
	{
		Bureaucrat bottom("Scruffy", 150);

		try
		{
			bottom.decrementGrade();
		}
		catch (std::exception& e)
		{
			std::cout << "Caught: " << e.what() << std::endl;
		}
		std::cout << "unchanged: " << bottom << std::endl;
	}

	std::cout << std::endl << "=== Test: copy and assignment ===" << std::endl;
	{
		Bureaucrat original("Bender Bending Rodriguez", 42);
		Bureaucrat copy(original);
		Bureaucrat assigned("Turanga Leela", 100);

		assigned = original;
		std::cout << original << std::endl;
		std::cout << copy << std::endl;
		std::cout << assigned << " (name stays: it is const)" << std::endl;
	}

	std::cout << std::endl << "=== End of tests ===" << std::endl;
	return 0;
}
