#include "Fixed.hpp"
#include <iostream>

const int Fixed::bits = 8;

Fixed::Fixed() : value(0) {
    std::cout << "Default Constructor called." << std::endl;
}

Fixed::Fixed(const Fixed &source) : 
value(source.value) {
    std::cout << "Copy Constructor called." << std::endl;
}

Fixed &Fixed::operator=(const Fixed &source) {
    if (this != &source) {
        value = source.value;
    }
    std::cout << "Copy Assignment Operator called." << std::endl;
    return *this;
}

Fixed::~Fixed() {
    std::cout << "Destructor called." << std::endl;
}

void Fixed::setRawBits(int const raw) {
    value = raw;
	std::cout << "setRawBits memeber function called" << std::endl;
}

int Fixed::getRawBits(void) const {
	std::cout << "getRawBits memeber function called" << std::endl;
    return value;
}
