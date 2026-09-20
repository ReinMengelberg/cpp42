#include "ScalarConverter.hpp"

#include <cctype>
#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

enum LiteralType {
	CHAR_LITERAL,
	INT_LITERAL,
	FLOAT_LITERAL,
	DOUBLE_LITERAL,
	INVALID_LITERAL
};

static const int	FLOAT_DIGITS = std::numeric_limits<float>::digits10;
static const int	DOUBLE_DIGITS = std::numeric_limits<double>::digits10;

/* ------------------------------------------------------------------ helpers */

static bool	isNotANumber(double value)
{
	return value != value;
}

static bool	isInfinite(double value)
{
	return value == std::numeric_limits<double>::infinity()
		|| value == -std::numeric_limits<double>::infinity();
}

static bool	isDigit(char c)
{
	return std::isdigit(static_cast<unsigned char>(c)) != 0;
}

/* --------------------------------------------------------- type detection */

static bool	isFloatPseudoLiteral(const std::string& literal)
{
	return literal == "nanf" || literal == "+inff" || literal == "-inff"
		|| literal == "inff";
}

static bool	isDoublePseudoLiteral(const std::string& literal)
{
	return literal == "nan" || literal == "+inf" || literal == "-inf"
		|| literal == "inf";
}

static bool	isCharLiteral(const std::string& literal)
{
	if (literal.length() == 3)
		return literal[0] == '\'' && literal[2] == '\'';
	return literal.length() == 1 && !isDigit(literal[0]);
}

static bool	isIntLiteral(const std::string& literal)
{
	std::string::size_type	i = 0;

	if (literal[i] == '+' || literal[i] == '-')
		i++;
	if (i == literal.length())
		return false;
	for (; i < literal.length(); i++)
		if (!isDigit(literal[i]))
			return false;

	errno = 0;
	long	value = std::strtol(literal.c_str(), NULL, 10);

	return errno != ERANGE
		&& value >= std::numeric_limits<int>::min()
		&& value <= std::numeric_limits<int>::max();
}

static bool	isDecimalNotation(const std::string& literal)
{
	std::string::size_type	i = 0;
	bool					hasDigits = false;

	if (i < literal.length() && (literal[i] == '+' || literal[i] == '-'))
		i++;
	for (; i < literal.length() && isDigit(literal[i]); i++)
		hasDigits = true;
	if (i < literal.length() && literal[i] == '.')
		for (i++; i < literal.length() && isDigit(literal[i]); i++)
			hasDigits = true;
	if (!hasDigits)
		return false;
	if (i < literal.length() && (literal[i] == 'e' || literal[i] == 'E'))
	{
		i++;
		if (i < literal.length() && (literal[i] == '+' || literal[i] == '-'))
			i++;
		if (i == literal.length() || !isDigit(literal[i]))
			return false;
		while (i < literal.length() && isDigit(literal[i]))
			i++;
	}
	return i == literal.length();
}

static bool	isFloatLiteral(const std::string& literal)
{
	if (literal.length() < 2 || literal[literal.length() - 1] != 'f')
		return false;

	std::string	number = literal.substr(0, literal.length() - 1);

	return isDecimalNotation(number)
		&& !isInfinite(static_cast<float>(std::atof(number.c_str())));
}

static bool	isDoubleLiteral(const std::string& literal)
{
	return isDecimalNotation(literal)
		&& !isInfinite(std::atof(literal.c_str()));
}

static LiteralType	detectType(const std::string& literal)
{
	if (literal.empty())
		return INVALID_LITERAL;
	if (isFloatPseudoLiteral(literal))
		return FLOAT_LITERAL;
	if (isDoublePseudoLiteral(literal))
		return DOUBLE_LITERAL;
	if (isCharLiteral(literal))
		return CHAR_LITERAL;
	if (isIntLiteral(literal))
		return INT_LITERAL;
	if (isFloatLiteral(literal))
		return FLOAT_LITERAL;
	if (isDoubleLiteral(literal))
		return DOUBLE_LITERAL;
	return INVALID_LITERAL;
}

static char	parseChar(const std::string& literal)
{
	if (literal.length() == 3)
		return literal[1];
	return literal[0];
}

static double	parsePseudoLiteral(const std::string& literal)
{
	if (literal[0] == 'n')
		return std::numeric_limits<double>::quiet_NaN();
	if (literal[0] == '-')
		return -std::numeric_limits<double>::infinity();
	return std::numeric_limits<double>::infinity();
}

static float	parseFloat(const std::string& literal)
{
	if (isFloatPseudoLiteral(literal))
		return static_cast<float>(parsePseudoLiteral(literal));
	return static_cast<float>(std::atof(literal.c_str()));
}

static double	parseDouble(const std::string& literal)
{
	if (isDoublePseudoLiteral(literal))
		return parsePseudoLiteral(literal);
	return std::atof(literal.c_str());
}

static void	printImpossible(const char* type)
{
	std::cout << type << ": impossible" << std::endl;
}

static void	printChar(char value)
{
	std::cout << "char: ";
	if (std::isprint(static_cast<unsigned char>(value)))
		std::cout << "'" << value << "'" << std::endl;
	else
		std::cout << "Non displayable" << std::endl;
}

static void	printInt(int value)
{
	std::cout << "int: " << value << std::endl;
}

static std::string	formatFloatingPoint(double value, int digits, const char* suffix)
{
	std::ostringstream	out;

	if (isNotANumber(value))
		out << "nan";
	else if (isInfinite(value))
		out << (value < 0 ? "-inf" : "+inf");
	else if (value == std::floor(value) && std::fabs(value) < 1e15)
		out << std::fixed << std::setprecision(1) << value;
	else
		out << std::setprecision(digits) << value;
	out << suffix;
	return out.str();
}

static void	printFloat(float value)
{
	std::cout << "float: " << formatFloatingPoint(value, FLOAT_DIGITS, "f") << std::endl;
}

static void	printDouble(double value, int digits)
{
	std::cout << "double: " << formatFloatingPoint(value, digits, "") << std::endl;
}

static bool	fitsInChar(double value)
{
	return !isNotANumber(value)
		&& value >= std::numeric_limits<char>::min()
		&& value <= std::numeric_limits<char>::max();
}

static bool	fitsInInt(double value)
{
	return !isNotANumber(value)
		&& value >= std::numeric_limits<int>::min()
		&& value <= std::numeric_limits<int>::max();
}

static void	convertFromChar(char value)
{
	printChar(value);
	printInt(static_cast<int>(value));
	printFloat(static_cast<float>(value));
	printDouble(static_cast<double>(value), DOUBLE_DIGITS);
}

static void	convertFromInt(int value)
{
	if (fitsInChar(value))
		printChar(static_cast<char>(value));
	else
		printImpossible("char");
	printInt(value);
	printFloat(static_cast<float>(value));
	printDouble(static_cast<double>(value), DOUBLE_DIGITS);
}

static void	convertFromFloat(float value)
{
	if (fitsInChar(value))
		printChar(static_cast<char>(value));
	else
		printImpossible("char");
	if (fitsInInt(value))
		printInt(static_cast<int>(value));
	else
		printImpossible("int");
	printFloat(value);
	// The double made from a float carries no more digits than the float did.
	printDouble(static_cast<double>(value), FLOAT_DIGITS);
}

static void	convertFromDouble(double value)
{
	float	asFloat = static_cast<float>(value);

	if (fitsInChar(value))
		printChar(static_cast<char>(value));
	else
		printImpossible("char");
	if (fitsInInt(value))
		printInt(static_cast<int>(value));
	else
		printImpossible("int");
	// A finite double that turns into an infinite float has overflowed.
	if (isInfinite(asFloat) && !isInfinite(value))
		printImpossible("float");
	else
		printFloat(asFloat);
	printDouble(value, DOUBLE_DIGITS);
}

void ScalarConverter::convert(const std::string& literal)
{
	switch (detectType(literal))
	{
		case CHAR_LITERAL:
			convertFromChar(parseChar(literal));
			break;
		case INT_LITERAL:
			convertFromInt(std::atoi(literal.c_str()));
			break;
		case FLOAT_LITERAL:
			convertFromFloat(parseFloat(literal));
			break;
		case DOUBLE_LITERAL:
			convertFromDouble(parseDouble(literal));
			break;
		default:
			printImpossible("char");
			printImpossible("int");
			printImpossible("float");
			printImpossible("double");
	}
}
