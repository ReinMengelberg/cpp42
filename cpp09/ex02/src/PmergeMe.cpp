#include "PmergeMe.hpp"

#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sys/time.h>

// ---------------------------------------------------------------- helpers --

static double	nowInMicroseconds()
{
	struct timeval	moment;

	gettimeofday(&moment, NULL);
	return static_cast<double>(moment.tv_sec) * 1000000.0
		+ static_cast<double>(moment.tv_usec);
}

// Both sorts work on indices rather than on values: an index identifies one
// element for sure, so a small element never loses track of the large one it
// was paired with, even when the sequence contains equal values.

struct VectorLess {
	const std::vector<int>*	key;

	bool	operator()(std::size_t index, int value) const
	{
		return (*key)[index] < value;
	}
};

struct DequeLess {
	const std::deque<int>*	key;

	bool	operator()(std::size_t index, int value) const
	{
		return (*key)[index] < value;
	}
};

// ----------------------------------------------------------- vector sorts --

static void	vectorMergeInsert(std::vector<std::size_t>& order, const std::vector<int>& key)
{
	if (order.size() < 2)
		return;

	const bool	hasStraggler = order.size() % 2 == 1;
	std::size_t	straggler = 0;

	if (hasStraggler)
	{
		straggler = order.back();
		order.pop_back();
	}

	std::vector<std::size_t>	larger;
	std::vector<std::size_t>	partnerOf(key.size(), 0);

	for (std::size_t i = 0; i + 1 < order.size(); i += 2)
	{
		std::size_t	high = order[i];
		std::size_t	low = order[i + 1];

		if (key[high] < key[low])
			std::swap(high, low);
		larger.push_back(high);
		partnerOf[high] = low;
	}

	// Sorting the large elements of every pair is the same problem, half the size.
	vectorMergeInsert(larger, key);

	// The chain opens with the partner of the smallest large element: it is
	// smaller than that one, hence smaller than every other large element.
	std::vector<std::size_t>	chain;
	std::vector<std::size_t>	positionOfLarge(larger.size(), 0);

	chain.push_back(partnerOf[larger[0]]);
	for (std::size_t i = 0; i < larger.size(); i++)
	{
		chain.push_back(larger[i]);
		positionOfLarge[i] = i + 1;
	}

	VectorLess	comparator;

	comparator.key = &key;

	// The remaining small elements go in following the Jacobsthal numbers
	// (1, 3, 5, 11, 21...), each search bounded by where its own partner sits.
	std::size_t	inserted = 1;
	std::size_t	previousJacobsthal = 1;
	std::size_t	currentJacobsthal = 3;

	while (inserted < larger.size())
	{
		const std::size_t	groupEnd = currentJacobsthal < larger.size()
			? currentJacobsthal : larger.size();

		for (std::size_t i = groupEnd; i > inserted; i--)
		{
			const std::size_t					small = partnerOf[larger[i - 1]];
			std::vector<std::size_t>::iterator	limit =
				chain.begin() + static_cast<std::ptrdiff_t>(positionOfLarge[i - 1]);
			std::vector<std::size_t>::iterator	where =
				std::lower_bound(chain.begin(), limit, key[small], comparator);
			const std::size_t					offset =
				static_cast<std::size_t>(where - chain.begin());

			chain.insert(where, small);
			for (std::size_t j = 0; j < positionOfLarge.size(); j++)
			{
				if (positionOfLarge[j] >= offset)
					positionOfLarge[j]++;
			}
		}
		inserted = groupEnd;

		const std::size_t	following = currentJacobsthal + 2 * previousJacobsthal;

		previousJacobsthal = currentJacobsthal;
		currentJacobsthal = following;
	}

	if (hasStraggler)
	{
		std::vector<std::size_t>::iterator	where =
			std::lower_bound(chain.begin(), chain.end(), key[straggler], comparator);

		chain.insert(where, straggler);
	}
	order = chain;
}

void PmergeMe::sortVector(std::vector<int>& data)
{
	if (data.size() < 2)
		return;

	std::vector<std::size_t>	order(data.size());

	for (std::size_t i = 0; i < data.size(); i++)
		order[i] = i;
	vectorMergeInsert(order, data);

	std::vector<int>	sorted;

	sorted.reserve(data.size());
	for (std::size_t i = 0; i < order.size(); i++)
		sorted.push_back(data[order[i]]);
	data = sorted;
}

// ------------------------------------------------------------ deque sorts --

static void	dequeMergeInsert(std::deque<std::size_t>& order, const std::deque<int>& key)
{
	if (order.size() < 2)
		return;

	const bool	hasStraggler = order.size() % 2 == 1;
	std::size_t	straggler = 0;

	if (hasStraggler)
	{
		straggler = order.back();
		order.pop_back();
	}

	std::deque<std::size_t>	larger;
	std::deque<std::size_t>	partnerOf(key.size(), 0);

	for (std::size_t i = 0; i + 1 < order.size(); i += 2)
	{
		std::size_t	high = order[i];
		std::size_t	low = order[i + 1];

		if (key[high] < key[low])
			std::swap(high, low);
		larger.push_back(high);
		partnerOf[high] = low;
	}

	dequeMergeInsert(larger, key);

	std::deque<std::size_t>	chain;
	std::deque<std::size_t>	positionOfLarge(larger.size(), 0);

	chain.push_back(partnerOf[larger[0]]);
	for (std::size_t i = 0; i < larger.size(); i++)
	{
		chain.push_back(larger[i]);
		positionOfLarge[i] = i + 1;
	}

	DequeLess	comparator;

	comparator.key = &key;

	std::size_t	inserted = 1;
	std::size_t	previousJacobsthal = 1;
	std::size_t	currentJacobsthal = 3;

	while (inserted < larger.size())
	{
		const std::size_t	groupEnd = currentJacobsthal < larger.size()
			? currentJacobsthal : larger.size();

		for (std::size_t i = groupEnd; i > inserted; i--)
		{
			const std::size_t					small = partnerOf[larger[i - 1]];
			std::deque<std::size_t>::iterator	limit =
				chain.begin() + static_cast<std::ptrdiff_t>(positionOfLarge[i - 1]);
			std::deque<std::size_t>::iterator	where =
				std::lower_bound(chain.begin(), limit, key[small], comparator);
			const std::size_t					offset =
				static_cast<std::size_t>(where - chain.begin());

			chain.insert(where, small);
			for (std::size_t j = 0; j < positionOfLarge.size(); j++)
			{
				if (positionOfLarge[j] >= offset)
					positionOfLarge[j]++;
			}
		}
		inserted = groupEnd;

		const std::size_t	following = currentJacobsthal + 2 * previousJacobsthal;

		previousJacobsthal = currentJacobsthal;
		currentJacobsthal = following;
	}

	if (hasStraggler)
	{
		std::deque<std::size_t>::iterator	where =
			std::lower_bound(chain.begin(), chain.end(), key[straggler], comparator);

		chain.insert(where, straggler);
	}
	order = chain;
}

void PmergeMe::sortDeque(std::deque<int>& data)
{
	if (data.size() < 2)
		return;

	std::deque<std::size_t>	order(data.size());

	for (std::size_t i = 0; i < data.size(); i++)
		order[i] = i;
	dequeMergeInsert(order, data);

	std::deque<int>	sorted;

	for (std::size_t i = 0; i < order.size(); i++)
		sorted.push_back(data[order[i]]);
	data = sorted;
}

// ------------------------------------------------------------------ class --

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe& other)
	: vectorData(other.vectorData), dequeData(other.dequeData)
{
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		vectorData = other.vectorData;
		dequeData = other.dequeData;
	}
	return *this;
}

PmergeMe::~PmergeMe()
{
}

static bool	parsePositiveInteger(const std::string& text, int& result)
{
	if (text.empty())
		return false;
	for (std::string::size_type i = 0; i < text.length(); i++)
	{
		if (text[i] < '0' || text[i] > '9')
			return false;
	}

	char*			end = NULL;
	const long		parsed = std::strtol(text.c_str(), &end, 10);

	if (*end != '\0' || parsed > 2147483647L)
		return false;
	result = static_cast<int>(parsed);
	return true;
}

void PmergeMe::parse(int argc, char** argv)
{
	if (argc < 2)
		throw PmergeMe::InvalidInputException();
	for (int i = 1; i < argc; i++)
	{
		int	value = 0;

		if (!parsePositiveInteger(argv[i], value))
			throw PmergeMe::InvalidInputException();
		vectorData.push_back(value);
		dequeData.push_back(value);
	}
}

static void	printSequence(const std::string& label, const std::vector<int>& data)
{
	std::cout << label;
	for (std::size_t i = 0; i < data.size(); i++)
		std::cout << " " << data[i];
	std::cout << std::endl;
}

void PmergeMe::run() const
{
	printSequence("Before:", vectorData);

	// Both timings cover the whole job: building the working container and
	// sorting it.
	const double		vectorStart = nowInMicroseconds();
	std::vector<int>	sortedVector(vectorData);

	PmergeMe::sortVector(sortedVector);

	const double		vectorEnd = nowInMicroseconds();
	const double		dequeStart = nowInMicroseconds();
	std::deque<int>		sortedDeque(dequeData);

	PmergeMe::sortDeque(sortedDeque);

	const double		dequeEnd = nowInMicroseconds();

	printSequence("After: ", sortedVector);

	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << vectorData.size()
		<< " elements with std::vector : " << vectorEnd - vectorStart << " us" << std::endl;
	std::cout << "Time to process a range of " << dequeData.size()
		<< " elements with std::deque  : " << dequeEnd - dequeStart << " us" << std::endl;
}

const char* PmergeMe::InvalidInputException::what() const throw()
{
	return "Error";
}
