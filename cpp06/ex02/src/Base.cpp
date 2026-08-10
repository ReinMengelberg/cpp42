#include "A.hpp"
#include "B.hpp"
#include "Base.hpp"
#include "C.hpp"

#include <cstdlib>
#include <exception>
#include <iostream>

// Only dynamic_cast can tell what a polymorphic object really is at runtime,
// which is exactly what identify() needs.

Base::~Base()
{
}

Base* generate(void)
{
	switch (std::rand() % 3)
	{
		case 0:
			return new A();
		case 1:
			return new B();
		default:
			return new C();
	}
}

void identify(Base* p)
{
	// On a pointer, a failed dynamic_cast simply gives NULL.
	if (dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "C" << std::endl;
	else
		std::cout << "Unknown type" << std::endl;
}

void identify(Base& p)
{
	// On a reference, a failed dynamic_cast throws std::bad_cast instead.
	// Catching it as a std::exception avoids including <typeinfo>.
	try
	{
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
		return;
	}
	catch (std::exception&)
	{
	}
	try
	{
		(void)dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
		return;
	}
	catch (std::exception&)
	{
	}
	try
	{
		(void)dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
		return;
	}
	catch (std::exception&)
	{
	}
	std::cout << "Unknown type" << std::endl;
}
