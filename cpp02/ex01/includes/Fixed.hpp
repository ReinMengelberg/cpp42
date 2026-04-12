#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed {
	public:
		Fixed();
		Fixed(const int value);
		Fixed(const float value);
		Fixed(const Fixed &source);
		Fixed &operator=(const Fixed &source);
		~Fixed();

		int getRawBits(void) const;
		void setRawBits(int const raw);
		float toFloat(void) const;
		int toInt(void) const;

	private:
		int _value;
		static const int _bits;
};

std::ostream &operator<<(std::ostream &out, const Fixed &fixed);

#endif