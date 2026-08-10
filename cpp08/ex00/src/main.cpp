#include "easyfind.hpp"

#include <deque>
#include <iostream>
#include <list>
#include <vector>

int main(void)
{
	std::cout << "=== Test: a vector ===" << std::endl;
	{
		std::vector<int>	numbers;

		for (int i = 0; i < 10; i++)
			numbers.push_back(i * 3);

		try
		{
			std::vector<int>::iterator	it = easyfind(numbers, 21);

			std::cout << "found " << *it << " at index "
				<< std::distance(numbers.begin(), it) << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << "Caught: " << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== Test: value that is not there ===" << std::endl;
	{
		std::vector<int>	numbers;

		numbers.push_back(1);
		numbers.push_back(2);
		try
		{
			easyfind(numbers, 42);
			std::cout << "this line should never be reached" << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << "Caught: " << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== Test: the first occurrence is returned ===" << std::endl;
	{
		std::list<int>	numbers;

		numbers.push_back(7);
		numbers.push_back(4);
		numbers.push_back(7);

		std::list<int>::iterator	it = easyfind(numbers, 7);

		std::cout << "index of the first 7: "
			<< std::distance(numbers.begin(), it) << std::endl;
	}

	std::cout << std::endl << "=== Test: a deque, and a const container ===" << std::endl;
	{
		std::deque<int>	numbers;

		numbers.push_back(10);
		numbers.push_back(20);
		numbers.push_back(30);

		const std::deque<int>&	readOnly = numbers;

		std::cout << "found " << *easyfind(readOnly, 20) << " in a const deque" << std::endl;

		// The iterator stays usable: the caller can modify what it points to.
		*easyfind(numbers, 30) = 42;
		std::cout << "last element is now " << numbers.back() << std::endl;
	}

	std::cout << std::endl << "=== Test: an empty container ===" << std::endl;
	{
		std::vector<int>	empty;

		try
		{
			easyfind(empty, 0);
		}
		catch (const std::exception& e)
		{
			std::cout << "Caught: " << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== End of tests ===" << std::endl;
	return 0;
}
