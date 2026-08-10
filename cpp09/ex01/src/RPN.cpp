#include "RPN.hpp"

#include <sstream>

static bool	isOperator(const std::string& token)
{
	return token.length() == 1
		&& (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/');
}

static bool	isSingleDigit(const std::string& token)
{
	return token.length() == 1 && token[0] >= '0' && token[0] <= '9';
}

RPN::RPN()
{
}

RPN::RPN(const RPN& other) : operands(other.operands)
{
}

RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
		operands = other.operands;
	return *this;
}

RPN::~RPN()
{
}

void RPN::applyOperator(char symbol)
{
	if (operands.size() < 2)
		throw RPN::InvalidExpressionException();

	const double	right = operands.top();

	operands.pop();

	const double	left = operands.top();

	operands.pop();
	switch (symbol)
	{
		case '+':
			operands.push(left + right);
			break;
		case '-':
			operands.push(left - right);
			break;
		case '*':
			operands.push(left * right);
			break;
		default:
			if (right == 0.0)
				throw RPN::DivisionByZeroException();
			operands.push(left / right);
			break;
	}
}

double RPN::evaluate(const std::string& expression)
{
	std::istringstream	stream(expression);
	std::string			token;

	while (!operands.empty())
		operands.pop();
	while (stream >> token)
	{
		if (isSingleDigit(token))
			operands.push(static_cast<double>(token[0] - '0'));
		else if (isOperator(token))
			applyOperator(token[0]);
		else
			throw RPN::InvalidExpressionException();
	}
	// Exactly one value must be left, otherwise the expression was incomplete.
	if (operands.size() != 1)
		throw RPN::InvalidExpressionException();
	return operands.top();
}

const char* RPN::InvalidExpressionException::what() const throw()
{
	return "invalid expression.";
}

const char* RPN::DivisionByZeroException::what() const throw()
{
	return "division by zero.";
}
