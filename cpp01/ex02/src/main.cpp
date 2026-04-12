#include <iostream>

int main (void) {
	std::string brainz = "HI THIS IS BRAIN";
	std::string *stringPTR = &brainz;
	std::string &stringREF = brainz;

	std::cout << "Adress of string:         " << &brainz << '\n';
	std::cout << "Adress held by pointer:   " << stringPTR << '\n';
	std::cout << "Adress held by reference: " << &stringREF << '\n';

	std::cout << "Value of string:          " << brainz << '\n';
	std::cout << "Value at pointer:         " << *stringPTR << '\n';
	std::cout << "Value at reference:       " << stringREF << '\n';

	return 0;
}