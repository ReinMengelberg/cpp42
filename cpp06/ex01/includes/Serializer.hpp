#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include "Data.hpp"

#include <stdint.h>

class Serializer {
private:
	// Nothing to store, so the class must not be instantiable: the canonical
	// form is kept private and left undefined on purpose.
	Serializer();
	Serializer(const Serializer& other);
	Serializer& operator=(const Serializer& other);
	~Serializer();

public:
	static uintptr_t	serialize(Data* ptr);
	static Data*		deserialize(uintptr_t raw);
};

#endif
