#include "Fixed.hpp"
#include <iostream>
#include <cmath>

const int Fixed::bits = 8;

Fixed::Fixed() : value(0) {
}

Fixed::Fixed(const int value) : value(value << bits) {
}

Fixed::Fixed(const float value) : value(roundf(value * (1 << bits))) {
}

Fixed::Fixed(const Fixed &source) : value(source.value) {
}

Fixed &Fixed::operator=(const Fixed &source) {
    if (this != &source) {
        value = source.value;
    }
    return *this;
}

Fixed::~Fixed() {
}

int Fixed::getRawBits(void) const {
    return value;
}

void Fixed::setRawBits(int const raw) {
    value = raw;
}

float Fixed::toFloat(void) const {
    return (float)value / (1 << bits);
}

int Fixed::toInt(void) const {
    return value >> bits;
}

bool Fixed::operator>(const Fixed &other) const {
    return value > other.value;
}

bool Fixed::operator<(const Fixed &other) const {
    return value < other.value;
}

bool Fixed::operator>=(const Fixed &other) const {
    return value >= other.value;
}

bool Fixed::operator<=(const Fixed &other) const {
    return value <= other.value;
}

bool Fixed::operator==(const Fixed &other) const {
    return value == other.value;
}

bool Fixed::operator!=(const Fixed &other) const {
    return value != other.value;
}

Fixed Fixed::operator+(const Fixed &other) const {
    Fixed result;
    result.setRawBits(value + other.value);
    return result;
}

Fixed Fixed::operator-(const Fixed &other) const {
    Fixed result;
    result.setRawBits(value - other.value);
    return result;
}

Fixed Fixed::operator*(const Fixed &other) const {
    Fixed result;
    result.setRawBits((long)value * other.value >> bits);
    return result;
}

Fixed Fixed::operator/(const Fixed &other) const {
    Fixed result;
    result.setRawBits(((long)value << bits) / other.value);
    return result;
}

Fixed &Fixed::operator++(void) {
    value++;
    return *this;
}

Fixed Fixed::operator++(int) {
    Fixed tmp(*this);
    value++;
    return tmp;
}

Fixed &Fixed::operator--(void) {
    value--;
    return *this;
}

Fixed Fixed::operator--(int) {
    Fixed tmp(*this);
    value--;
    return tmp;
}

Fixed &Fixed::min(Fixed &a, Fixed &b) {
    return (a < b) ? a : b;
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b) {
    return (a < b) ? a : b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b) {
    return (a > b) ? a : b;
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b) {
    return (a > b) ? a : b;
}

std::ostream &operator<<(std::ostream &out, const Fixed &fixed) {
    out << fixed.toFloat();
    return out;
}
