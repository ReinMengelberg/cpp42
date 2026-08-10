#include "ScalarConverter.hpp"

#include <cctype>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

// Every conversion below is a plain, well defined conversion between scalar
// types, so static_cast is the cast this exercise needs.

enum LiteralType {
	CHAR_LITERAL,
	INT_LITERAL,
	FLOAT_LITERAL,
	DOUBLE_LITERAL,
	INVALID_LITERAL
};

static bool	isInfinite(double value)
{
	return value == std::numeric_limits<double>::infinity()
		|| value == -std::numeric_limits<double>::infinity();
}

static bool	isNotANumber(double value)
{
	return value != value;
}

static bool	isCharLiteral(const std::string& literal)
{
	if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')
		return true;
	return literal.length() == 1
		&& !std::isdigit(static_cast<unsigned char>(literal[0]));
}

static bool	isIntLiteral(const std::string& literal)
{
	std::string::size_type	i = 0;

	if (literal[i] == '+' || literal[i] == '-')
		i++;
	if (i == literal.length())
		return false;
	while (i < literal.length())
	{
		if (!std::isdigit(static_cast<unsigned char>(literal[i])))
			return false;
		i++;
	}
	return true;
}

// Returns true when strtod() manages to read the whole string, except for the
// trailing characters left in `remainder` (the "f" suffix of a float).
static bool	parsesFully(const std::string& literal, const char* remainder)
{
	char*	end = NULL;

	std::strtod(literal.c_str(), &end);
	if (end == literal.c_str())
		return false;
	return std::string(end) == remainder;
}

static LiteralType	detectType(const std::string& literal)
{
	if (literal.empty())
		return INVALID_LITERAL;
	if (literal == "nanf" || literal == "+inff" || literal == "-inff" || literal == "inff")
		return FLOAT_LITERAL;
	if (literal == "nan" || literal == "+inf" || literal == "-inf" || literal == "inf")
		return DOUBLE_LITERAL;
	if (isCharLiteral(literal))
		return CHAR_LITERAL;
	if (isIntLiteral(literal))
		return INT_LITERAL;
	if (literal[literal.length() - 1] == 'f' && parsesFully(literal, "f"))
		return FLOAT_LITERAL;
	if (parsesFully(literal, ""))
		return DOUBLE_LITERAL;
	return INVALID_LITERAL;
}

static char	extractChar(const std::string& literal)
{
	if (literal.length() == 3)
		return literal[1];
	return literal[0];
}

static double	extractPseudoLiteral(const std::string& literal)
{
	if (literal == "nan" || literal == "nanf")
		return std::numeric_limits<double>::quiet_NaN();
	if (literal[0] == '-')
		return -std::numeric_limits<double>::infinity();
	return std::numeric_limits<double>::infinity();
}

static bool	isPseudoLiteral(const std::string& literal)
{
	return literal == "nan" || literal == "nanf"
		|| literal == "inf" || literal == "inff"
		|| literal == "+inf" || literal == "+inff"
		|| literal == "-inf" || literal == "-inff";
}

// Whole numbers must still show a decimal part ("42.0f"), the others are
// printed with the default precision of the stream ("4.2f").
static std::string	formatFloatingPoint(double value, bool isFloat)
{
	std::ostringstream	out;

	if (isNotANumber(value))
		return isFloat ? "nanf" : "nan";
	if (isInfinite(value))
		return value < 0 ? (isFloat ? "-inff" : "-inf") : (isFloat ? "+inff" : "+inf");
	if (value == std::floor(value) && std::fabs(value) < 1e16)
		out << std::fixed << std::setprecision(1) << value;
	else
		out << value;
	if (isFloat)
		out << "f";
	return out.str();
}

static void	displayChar(double value)
{
	std::cout << "char: ";
	if (isNotANumber(value) || isInfinite(value)
		|| value < static_cast<double>(std::numeric_limits<char>::min())
		|| value > static_cast<double>(std::numeric_limits<char>::max()))
	{
		std::cout << "impossible" << std::endl;
		return;
	}

	char	c = static_cast<char>(value);

	if (!std::isprint(static_cast<unsigned char>(c)))
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "'" << c << "'" << std::endl;
}

static void	displayInt(double value)
{
	std::cout << "int: ";
	if (isNotANumber(value) || isInfinite(value)
		|| value < static_cast<double>(std::numeric_limits<int>::min())
		|| value > static_cast<double>(std::numeric_limits<int>::max()))
		std::cout << "impossible" << std::endl;
	else
		std::cout << static_cast<int>(value) << std::endl;
}

static void	displayFloat(double value)
{
	float	f = static_cast<float>(value);

	std::cout << "float: ";
	// A finite double that turns into an infinite float has overflowed.
	if (isInfinite(f) && !isInfinite(value) && !isNotANumber(value))
		std::cout << "impossible" << std::endl;
	else
		std::cout << formatFloatingPoint(static_cast<double>(f), true) << std::endl;
}

static void	displayDouble(double value)
{
	std::cout << "double: " << formatFloatingPoint(value, false) << std::endl;
}

void ScalarConverter::convert(const std::string& literal)
{
	LiteralType	type = detectType(literal);
	double		value = 0.0;

	if (type == INVALID_LITERAL)
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}

	if (type == CHAR_LITERAL)
		value = static_cast<double>(extractChar(literal));
	else if (isPseudoLiteral(literal))
		value = extractPseudoLiteral(literal);
	else if (type == FLOAT_LITERAL)
		value = static_cast<double>(static_cast<float>(std::strtod(literal.c_str(), NULL)));
	else
		value = std::strtod(literal.c_str(), NULL);

	displayChar(value);
	displayInt(value);
	displayFloat(value);
	displayDouble(value);
}
