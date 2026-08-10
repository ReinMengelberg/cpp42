#include "Span.hpp"

#include <algorithm>

Span::Span() : maxSize(0)
{
}

Span::Span(unsigned int n) : maxSize(n)
{
	numbers.reserve(n);
}

Span::Span(const Span& other) : maxSize(other.maxSize), numbers(other.numbers)
{
}

Span& Span::operator=(const Span& other)
{
	if (this != &other)
	{
		maxSize = other.maxSize;
		numbers = other.numbers;
	}
	return *this;
}

Span::~Span()
{
}

void Span::addNumber(int number)
{
	if (numbers.size() >= maxSize)
		throw Span::SpanIsFullException();
	numbers.push_back(number);
}

// The shortest span is the smallest gap between two neighbours once the
// numbers are sorted, so a sorted copy answers the question in one pass.
unsigned int Span::shortestSpan() const
{
	if (numbers.size() < 2)
		throw Span::NoSpanFoundException();

	std::vector<int>	sorted(numbers);

	std::sort(sorted.begin(), sorted.end());

	long	shortest = static_cast<long>(sorted[1]) - sorted[0];

	for (std::vector<int>::size_type i = 2; i < sorted.size(); i++)
	{
		long	gap = static_cast<long>(sorted[i]) - sorted[i - 1];

		if (gap < shortest)
			shortest = gap;
	}
	return static_cast<unsigned int>(shortest);
}

unsigned int Span::longestSpan() const
{
	if (numbers.size() < 2)
		throw Span::NoSpanFoundException();

	// The widest gap always separates the smallest and the largest number.
	const int	smallest = *std::min_element(numbers.begin(), numbers.end());
	const int	largest = *std::max_element(numbers.begin(), numbers.end());

	return static_cast<unsigned int>(static_cast<long>(largest) - smallest);
}

unsigned int Span::size() const
{
	return static_cast<unsigned int>(numbers.size());
}

unsigned int Span::capacity() const
{
	return maxSize;
}

const char* Span::SpanIsFullException::what() const throw()
{
	return "Span: no room left to store another number.";
}

const char* Span::NoSpanFoundException::what() const throw()
{
	return "Span: at least two numbers are needed to measure a span.";
}
