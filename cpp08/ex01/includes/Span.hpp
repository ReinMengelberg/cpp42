#ifndef SPAN_HPP
#define SPAN_HPP

#include <exception>
#include <vector>

class Span {
private:
	unsigned int		maxSize;
	std::vector<int>	numbers;

public:
	Span();
	Span(unsigned int n);
	Span(const Span& other);
	Span& operator=(const Span& other);
	~Span();

	void	addNumber(int number);

	// Filling the Span one call at a time is annoying, so a whole range of
	// iterators can be added at once. It is a template, so it is defined here.
	template <typename InputIterator>
	void	addNumbers(InputIterator first, InputIterator last)
	{
		for (InputIterator it = first; it != last; ++it)
			addNumber(*it);
	}

	unsigned int	shortestSpan() const;
	unsigned int	longestSpan() const;

	unsigned int	size() const;
	unsigned int	capacity() const;

	class SpanIsFullException : public std::exception {
	public:
		virtual const char*	what() const throw();
	};

	class NoSpanFoundException : public std::exception {
	public:
		virtual const char*	what() const throw();
	};
};

#endif
