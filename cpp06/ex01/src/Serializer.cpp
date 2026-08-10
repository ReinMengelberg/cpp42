#include "Serializer.hpp"

// Reinterpreting the bits of a pointer as an integer (and back) is exactly
// what reinterpret_cast is for: no other cast can do this conversion.

uintptr_t Serializer::serialize(Data* ptr)
{
	return reinterpret_cast<uintptr_t>(ptr);
}

Data* Serializer::deserialize(uintptr_t raw)
{
	return reinterpret_cast<Data*>(raw);
}
