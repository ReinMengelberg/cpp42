#include "PmergeMe.hpp"

#include <iostream>

int main(int argc, char** argv)
{
	PmergeMe	sorter;

	try
	{
		sorter.parse(argc, argv);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}
	sorter.run();
	return 0;
}
