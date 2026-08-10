#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <exception>
#include <string>
#include <vector>

// The same merge-insertion (Ford-Johnson) sort is written twice, once for
// std::vector and once for std::deque, so the two can be timed against each
// other.

class PmergeMe {
private:
	std::vector<int>	vectorData;
	std::deque<int>		dequeData;

public:
	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();

	void	parse(int argc, char** argv);
	void	run() const;

	static void	sortVector(std::vector<int>& data);
	static void	sortDeque(std::deque<int>& data);

	class InvalidInputException : public std::exception {
	public:
		virtual const char*	what() const throw();
	};
};

#endif
