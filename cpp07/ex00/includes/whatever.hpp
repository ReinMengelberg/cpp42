#ifndef WHATEVER_HPP
#define WHATEVER_HPP

// Function templates have to be defined in the header: the compiler needs the
// body to instantiate them for every type they are called with.

template <typename T>
void	swap(T& a, T& b)
{
	T	tmp = a;

	a = b;
	b = tmp;
}

// When both values are equal, neither is smaller (or greater) than the other,
// so the second one is returned.
template <typename T>
const T&	min(const T& a, const T& b)
{
	return a < b ? a : b;
}

template <typename T>
const T&	max(const T& a, const T& b)
{
	return a > b ? a : b;
}

#endif
