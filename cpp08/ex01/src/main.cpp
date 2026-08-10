#include "Span.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <list>
#include <vector>

int main(void)
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	std::cout << "=== Test: the subject's example ===" << std::endl;
	{
		Span	sp = Span(5);

		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);

		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
	}

	std::cout << std::endl << "=== Test: adding one number too many ===" << std::endl;
	{
		Span	sp(2);

		sp.addNumber(1);
		sp.addNumber(2);
		try
		{
			sp.addNumber(3);
		}
		catch (const std::exception& e)
		{
			std::cout << "Caught: " << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== Test: not enough numbers for a span ===" << std::endl;
	{
		Span	empty(5);
		Span	single(5);

		single.addNumber(42);
		try
		{
			empty.shortestSpan();
		}
		catch (const std::exception& e)
		{
			std::cout << "Caught (empty): " << e.what() << std::endl;
		}
		try
		{
			single.longestSpan();
		}
		catch (const std::exception& e)
		{
			std::cout << "Caught (one number): " << e.what() << std::endl;
		}
	}

	std::cout << std::endl << "=== Test: filling from a range of iterators ===" << std::endl;
	{
		std::list<int>	source;

		source.push_back(-10);
		source.push_back(0);
		source.push_back(4);
		source.push_back(5);

		Span	sp(10);

		sp.addNumbers(source.begin(), source.end());
		std::cout << "stored " << sp.size() << " numbers out of " << sp.capacity() << std::endl;
		std::cout << "shortest: " << sp.shortestSpan() << std::endl;
		std::cout << "longest:  " << sp.longestSpan() << std::endl;
	}

	std::cout << std::endl << "=== Test: 20000 random numbers ===" << std::endl;
	{
		Span				sp(20000);
		std::vector<int>	source;

		for (int i = 0; i < 20000; i++)
			source.push_back(std::rand());
		sp.addNumbers(source.begin(), source.end());

		std::cout << "stored " << sp.size() << " numbers" << std::endl;
		std::cout << "shortest: " << sp.shortestSpan() << std::endl;
		std::cout << "longest:  " << sp.longestSpan() << std::endl;
	}

	std::cout << std::endl << "=== Test: extreme values do not overflow ===" << std::endl;
	{
		Span	sp(2);

		sp.addNumber(std::numeric_limits<int>::min());
		sp.addNumber(std::numeric_limits<int>::max());
		std::cout << "longest: " << sp.longestSpan()
			<< " (expected 4294967295)" << std::endl;
	}

	std::cout << std::endl << "=== Test: identical numbers give a span of 0 ===" << std::endl;
	{
		Span	sp(3);

		sp.addNumber(7);
		sp.addNumber(7);
		sp.addNumber(7);
		std::cout << "shortest: " << sp.shortestSpan() << ", longest: "
			<< sp.longestSpan() << std::endl;
	}

	std::cout << std::endl << "=== Test: copy and assignment ===" << std::endl;
	{
		Span	original(3);

		original.addNumber(1);
		original.addNumber(100);

		Span	copy(original);
		Span	assigned(1);

		assigned = original;
		original.addNumber(50);

		std::cout << "original size: " << original.size()
			<< ", copy size: " << copy.size()
			<< ", assigned size: " << assigned.size() << std::endl;
		std::cout << "copy longest: " << copy.longestSpan() << std::endl;
	}

	std::cout << std::endl << "=== End of tests ===" << std::endl;
	return 0;
}
