#include "A.hpp"
#include "B.hpp"
#include "Base.hpp"
#include "C.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

int main(void)
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	std::cout << "=== Test: eight randomly generated objects ===" << std::endl;
	for (int i = 0; i < 8; i++)
	{
		Base*	object = generate();

		std::cout << "by pointer:   ";
		identify(object);
		std::cout << "by reference: ";
		identify(*object);
		delete object;
	}

	std::cout << std::endl << "=== Test: known types, to check the answers ===" << std::endl;
	{
		A	a;
		B	b;
		C	c;

		std::cout << "expected A -> ";
		identify(&a);
		std::cout << "expected B -> ";
		identify(&b);
		std::cout << "expected C -> ";
		identify(&c);

		Base&	ref = b;

		std::cout << "expected B (through a Base&) -> ";
		identify(ref);
	}

	std::cout << std::endl << "=== Test: a NULL pointer ===" << std::endl;
	{
		std::cout << "expected Unknown type -> ";
		identify(static_cast<Base*>(NULL));
	}

	std::cout << std::endl << "=== End of tests ===" << std::endl;
	return 0;
}
