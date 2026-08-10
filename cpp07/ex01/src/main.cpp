#include "iter.hpp"

#include <iostream>
#include <string>

template <typename T>
void	print(const T& element)
{
	std::cout << element << " ";
}

template <typename T>
void	twice(T& element)
{
	element += element;
}

void	shout(const std::string& word)
{
	std::cout << word << "! ";
}

int main(void)
{
	std::cout << "=== Test: printing an array of ints ===" << std::endl;
	{
		int	numbers[5] = {1, 2, 3, 4, 5};

		::iter(numbers, 5, ::print<int>);
		std::cout << std::endl;
	}

	std::cout << std::endl << "=== Test: modifying the elements in place ===" << std::endl;
	{
		int	numbers[5] = {1, 2, 3, 4, 5};

		::iter(numbers, 5, ::twice<int>);
		::iter(numbers, 5, ::print<int>);
		std::cout << std::endl;
	}

	std::cout << std::endl << "=== Test: an array of strings ===" << std::endl;
	{
		std::string	words[3] = {"hello", "template", "world"};

		::iter(words, 3, ::print<std::string>);
		std::cout << std::endl;
		::iter(words, 3, ::twice<std::string>);
		::iter(words, 3, ::print<std::string>);
		std::cout << std::endl;
	}

	std::cout << std::endl << "=== Test: a const array (T is deduced as const) ===" << std::endl;
	{
		const double	values[4] = {1.5, 2.5, 3.5, 4.5};

		::iter(values, 4, ::print<double>);
		std::cout << std::endl;
	}

	std::cout << std::endl << "=== Test: a plain function instead of a template ===" << std::endl;
	{
		std::string	words[2] = {"Odin", "Thor"};

		::iter(words, 2, ::shout);
		std::cout << std::endl;
	}

	std::cout << std::endl << "=== Test: an empty array and a NULL pointer ===" << std::endl;
	{
		int*	nothing = NULL;

		::iter(nothing, 0, ::print<int>);
		std::cout << "nothing printed, nothing crashed." << std::endl;
	}

	std::cout << std::endl << "=== End of tests ===" << std::endl;
	return 0;
}
