#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>
#include <stdexcept>

// T is expected to be a sequence container of integers. std::find already does
// the search, so easyfind only has to report what happens when nothing matches.

template <typename T>
typename T::iterator	easyfind(T& container, int value)
{
	typename T::iterator	it = std::find(container.begin(), container.end(), value);

	if (it == container.end())
		throw std::runtime_error("easyfind: no occurrence found.");
	return it;
}

template <typename T>
typename T::const_iterator	easyfind(const T& container, int value)
{
	typename T::const_iterator	it = std::find(container.begin(), container.end(), value);

	if (it == container.end())
		throw std::runtime_error("easyfind: no occurrence found.");
	return it;
}

#endif
