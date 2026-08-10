#ifndef ARRAY_TPP
#define ARRAY_TPP

// Definitions of the Array class template. They live in a header because the
// compiler needs them to instantiate the template for every T it is used with.

// new T[0] is a valid, empty allocation: nothing is reserved in advance and
// the destructor stays symmetrical.
template <typename T>
Array<T>::Array() : elements(new T[0]()), length(0)
{
}

template <typename T>
Array<T>::Array(unsigned int n) : elements(new T[n]()), length(n)
{
}

template <typename T>
Array<T>::Array(const Array& other) : elements(new T[other.length]()), length(other.length)
{
	for (unsigned int i = 0; i < length; i++)
		elements[i] = other.elements[i];
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other)
{
	if (this != &other)
	{
		T*	copy = new T[other.length]();

		for (unsigned int i = 0; i < other.length; i++)
			copy[i] = other.elements[i];
		delete[] elements;
		elements = copy;
		length = other.length;
	}
	return *this;
}

template <typename T>
Array<T>::~Array()
{
	delete[] elements;
}

template <typename T>
T& Array<T>::operator[](unsigned int index)
{
	if (index >= length)
		throw typename Array<T>::OutOfBoundsException();
	return elements[index];
}

template <typename T>
const T& Array<T>::operator[](unsigned int index) const
{
	if (index >= length)
		throw typename Array<T>::OutOfBoundsException();
	return elements[index];
}

template <typename T>
unsigned int Array<T>::size() const
{
	return length;
}

template <typename T>
const char* Array<T>::OutOfBoundsException::what() const throw()
{
	return "Array index is out of bounds.";
}

#endif
