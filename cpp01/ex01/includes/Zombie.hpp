// ./Zombie.hpp
#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP
#include <iostream>
#include <string>

class Zombie {
	public: 
		Zombie(void);
		~Zombie(void);

		void announce(void);
		std::string getName(void) const;
		void setName(const std::string &name);

	private:
		std::string name;
};

Zombie *zombieHorde(int N, std::string name);

#endif