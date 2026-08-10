#include "whatever.hpp"

#include <iostream>
#include <string>

class Awesome {
private:
	int	value;

public:
	Awesome(int value) : value(value) {}

	int	getValue() const { return value; }

	bool	operator<(const Awesome& other) const { return value < other.value; }
	bool	operator>(const Awesome& other) const { return value > other.value; }
};

std::ostream&	operator<<(std::ostream& out, const Awesome& awesome)
{
	out << awesome.getValue();
	return out;
}

int main(void)
{
	std::cout << "=== Test: the subject's example ===" << std::endl;
	{
		int	a = 2;
		int	b = 3;

		::swap(a, b);
		std::cout << "a = " << a << ", b = " << b << std::endl;
		std::cout << "min( a, b ) = " << ::min(a, b) << std::endl;
		std::cout << "max( a, b ) = " << ::max(a, b) << std::endl;

		std::string	c = "chaine1";
		std::string	d = "chaine2";

		::swap(c, d);
		std::cout << "c = " << c << ", d = " << d << std::endl;
		std::cout << "min( c, d ) = " << ::min(c, d) << std::endl;
		std::cout << "max( c, d ) = " << ::max(c, d) << std::endl;
	}

	std::cout << std::endl << "=== Test: equal values return the second one ===" << std::endl;
	{
		int	a = 42;
		int	b = 42;

		std::cout << "min returns the second: "
			<< (&::min(a, b) == &b ? "yes" : "no") << std::endl;
		std::cout << "max returns the second: "
			<< (&::max(a, b) == &b ? "yes" : "no") << std::endl;
	}

	std::cout << std::endl << "=== Test: other types ===" << std::endl;
	{
		double	e = 4.2;
		double	f = -4.2;

		::swap(e, f);
		std::cout << "e = " << e << ", f = " << f << std::endl;
		std::cout << "min( e, f ) = " << ::min(e, f) << std::endl;
		std::cout << "max( e, f ) = " << ::max(e, f) << std::endl;

		char	g = 'z';
		char	h = 'a';

		::swap(g, h);
		std::cout << "g = " << g << ", h = " << h << std::endl;
		std::cout << "min( g, h ) = " << ::min(g, h) << std::endl;
		std::cout << "max( g, h ) = " << ::max(g, h) << std::endl;
	}

	std::cout << std::endl << "=== Test: a user defined type ===" << std::endl;
	{
		Awesome	i(2);
		Awesome	j(7);

		::swap(i, j);
		std::cout << "i = " << i << ", j = " << j << std::endl;
		std::cout << "min( i, j ) = " << ::min(i, j) << std::endl;
		std::cout << "max( i, j ) = " << ::max(i, j) << std::endl;
	}

	std::cout << std::endl << "=== End of tests ===" << std::endl;
	return 0;
}
