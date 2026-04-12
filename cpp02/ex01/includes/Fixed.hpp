#ifndef FIXED_HPP
#define FIXED_HPP

class Fixed {
	public:
		Fixed();
		Fixed(const Fixed &source);
		Fixed &operator=(const Fixed &source);
		~Fixed();

		void setRawBits(int const raw);
		int getRawBits(void) const;

	private:
		int value;
		static const int bits;
};

#endif