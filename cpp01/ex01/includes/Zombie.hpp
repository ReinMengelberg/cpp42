// ./Zombie.hpp
#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP
#include <iostream>
#include <string>

class Zombie {
	public: 
		Zombie(void); // Constructor
		~Zombie(void); // Destructor

		void announce(void);
		std::string getName(void) const; // Added const for getter
		void setName(const std::string &name); // Added const 

	private:
		std::string name;
};

Zombie *zombieHorde(int N, std::string &name);

#endif