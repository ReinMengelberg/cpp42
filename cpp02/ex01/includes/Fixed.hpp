#ifndef FIXED_HPP
#define FIXED_HPP

class Fixed {
	public:
		Fixed(); // Constructor
		Fixed(const Fixed &source); // Copy Constructor
		Fixed &operator=(const Fixed &source); // Copy Assignment Operator

		
		~Fixed(); // Destructor

		void setRawBits(int const raw);
		int getRawBits(void) const;

	private:
		int value;
		static const int bits;
};

#endif