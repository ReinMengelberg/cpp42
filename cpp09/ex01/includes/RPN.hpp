#ifndef RPN_HPP
#define RPN_HPP

#include <exception>
#include <list>
#include <stack>
#include <string>

// Reverse Polish notation is evaluated with a stack: operands are pushed, an
// operator pops the last two and pushes the result back.
// std::stack is explicitly built on a std::list here so that this exercise
// does not reuse the containers of the other exercises of the module.

class RPN {
private:
	std::stack<double, std::list<double> >	operands;

	void	applyOperator(char symbol);

public:
	RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN();

	double	evaluate(const std::string& expression);

	class InvalidExpressionException : public std::exception {
	public:
		virtual const char*	what() const throw();
	};

	class DivisionByZeroException : public std::exception {
	public:
		virtual const char*	what() const throw();
	};
};

#endif
