#include "Fixed.hpp"
#include <iostream>

// Static member initialization
const int Fixed::bits = 8;

// Default Constructor
Fixed::Fixed() : value(0) {
    std::cout << "Default Constructor called." << std::endl;
}

// Copy Constructor
Fixed::Fixed(const Fixed &source) : 
value(source.value) {
    std::cout << "Copy Constructor called." << std::endl;
}

// Copy Assignment Operator
Fixed &Fixed::operator=(const Fixed &source) {
    if (this != &source) {  // Check for self-assignment
        value = source.value;
    }
    std::cout << "Copy Assignment Operator called." << std::endl;
    return *this;
}

// Destructor
Fixed::~Fixed() {
    std::cout << "Destructor called." << std::endl;
}

// Setter
void Fixed::setRawBits(int const raw) {
    value = raw;
	std::cout << "setRawBits member function called" << std::endl;
}

// Getter
int Fixed::getRawBits(void) const {
	std::cout << "getRawBits memeber function called" << std::endl;
    return value;
}
