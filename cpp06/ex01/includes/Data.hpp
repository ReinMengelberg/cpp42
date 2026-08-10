#ifndef DATA_HPP
#define DATA_HPP

#include <string>

// A plain, non empty structure: something has to be there to prove that the
// pointer survived the round trip.
struct Data {
	std::string	name;
	int			id;
	float		score;
};

#endif
