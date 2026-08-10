#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>

class ScalarConverter {
private:
	// The class holds nothing, so it must not be instantiable: the whole
	// canonical form is kept private and left undefined on purpose.
	ScalarConverter();
	ScalarConverter(const ScalarConverter& other);
	ScalarConverter& operator=(const ScalarConverter& other);
	~ScalarConverter();

public:
	static void	convert(const std::string& literal);
};

#endif
