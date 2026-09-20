#include "Data.hpp"
#include "Serializer.hpp"

#include <iostream>

int main(void)
{
	std::cout << std::endl << "=== Start Tests ===" << std::endl;
	Data	data;

	data.name = "Stacker";

	data.id = 98;
	data.score = 9.8f;

	std::cout << "=== Test: round trip on stack object ===" << std::endl;
	{
		uintptr_t	raw = Serializer::serialize(&data);
		Data*		restored = Serializer::deserialize(raw);

		std::cout << "original pointer: " << &data << std::endl;
		std::cout << "serialized value: " << raw << std::endl;
		std::cout << "restored pointer: " << restored << std::endl;
		std::cout << "pointers are " << (restored == &data ? "equal" : "different") << std::endl;
		std::cout << "restored data:    " << restored->name << ", id " << restored->id
			<< ", score " << restored->score << std::endl;
	}

	std::cout << std::endl << "=== Test: round trip on heap object ===" << std::endl;
	{
		Data*	heap = new Data();

		heap->name = "Heaper";
		heap->id = 5;
		heap->score = 3.5f;

		Data*	restored = Serializer::deserialize(Serializer::serialize(heap));

		std::cout << "pointers are " << (restored == heap ? "equal" : "different") << std::endl;
		std::cout << "restored data:    " << restored->name << ", id " << restored->id
			<< ", score " << restored->score << std::endl;
		delete heap;
	}

	std::cout << std::endl << "=== Test: NULL pointer ===" << std::endl;
	{
		uintptr_t	raw = Serializer::serialize(NULL);

		std::cout << "serialized NULL: " << raw << std::endl;
		std::cout << "pointers are "
			<< (Serializer::deserialize(raw) == NULL ? "equal" : "different") << std::endl;
	}

	std::cout << std::endl << "=== Completed tests ===" << std::endl;
	return 0;
}
