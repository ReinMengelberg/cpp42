#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef>

// T is deduced as `const X` when the array itself is const, so the same
// template covers const and non-const elements. Taking the function as a
// template parameter lets it be a function pointer, an instantiated function
// template or a functor, with a const or non-const reference parameter.

template <typename T, typename F>
void	iter(T* array, const size_t length, F function)
{
	if (!array)
		return;
	for (size_t i = 0; i < length; i++)
		function(array[i]);
}

#endif
