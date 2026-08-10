#include "MutantStack.hpp"

#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <vector>

int main(void)
{
	std::cout << "=== Test: the subject's example, with a MutantStack ===" << std::endl;
	{
		MutantStack<int>	mstack;

		mstack.push(5);
		mstack.push(17);
		std::cout << mstack.top() << std::endl;
		mstack.pop();
		std::cout << mstack.size() << std::endl;
		mstack.push(3);
		mstack.push(5);
		mstack.push(737);
		mstack.push(0);

		MutantStack<int>::iterator	it = mstack.begin();
		MutantStack<int>::iterator	ite = mstack.end();

		++it;
		--it;
		while (it != ite)
		{
			std::cout << *it << std::endl;
			++it;
		}

		std::stack<int>	s(mstack);
		std::cout << "copied into a std::stack, size " << s.size() << std::endl;
	}

	std::cout << std::endl << "=== Test: the same example with a std::list ===" << std::endl;
	{
		std::list<int>	mstack;

		mstack.push_back(5);
		mstack.push_back(17);
		std::cout << mstack.back() << std::endl;
		mstack.pop_back();
		std::cout << mstack.size() << std::endl;
		mstack.push_back(3);
		mstack.push_back(5);
		mstack.push_back(737);
		mstack.push_back(0);

		std::list<int>::iterator	it = mstack.begin();
		std::list<int>::iterator	ite = mstack.end();

		++it;
		--it;
		while (it != ite)
		{
			std::cout << *it << std::endl;
			++it;
		}
	}

	std::cout << std::endl << "=== Test: reverse iterators ===" << std::endl;
	{
		MutantStack<int>	mstack;

		for (int i = 1; i <= 5; i++)
			mstack.push(i);
		for (MutantStack<int>::reverse_iterator it = mstack.rbegin(); it != mstack.rend(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}

	std::cout << std::endl << "=== Test: a const MutantStack ===" << std::endl;
	{
		MutantStack<int>	mstack;

		mstack.push(1);
		mstack.push(2);
		mstack.push(3);

		const MutantStack<int>&	readOnly = mstack;

		for (MutantStack<int>::const_iterator it = readOnly.begin(); it != readOnly.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}

	std::cout << std::endl << "=== Test: the iterators work with the algorithms ===" << std::endl;
	{
		MutantStack<int>	mstack;

		mstack.push(42);
		mstack.push(7);
		mstack.push(19);

		std::cout << "max element: "
			<< *std::max_element(mstack.begin(), mstack.end()) << std::endl;
		std::cout << "is 19 there? "
			<< (std::find(mstack.begin(), mstack.end(), 19) != mstack.end() ? "yes" : "no")
			<< std::endl;
	}

	std::cout << std::endl << "=== Test: another type and another container ===" << std::endl;
	{
		MutantStack<std::string, std::vector<std::string> >	mstack;

		mstack.push("bottom");
		mstack.push("middle");
		mstack.push("top");

		MutantStack<std::string, std::vector<std::string> >	copy(mstack);

		copy.pop();
		std::cout << "original: ";
		for (MutantStack<std::string, std::vector<std::string> >::iterator it = mstack.begin();
			it != mstack.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl << "copy:     ";
		for (MutantStack<std::string, std::vector<std::string> >::iterator it = copy.begin();
			it != copy.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}

	std::cout << std::endl << "=== Test: an empty stack ===" << std::endl;
	{
		MutantStack<int>	mstack;

		std::cout << "empty: " << (mstack.begin() == mstack.end() ? "yes" : "no")
			<< ", size " << mstack.size() << std::endl;
	}

	std::cout << std::endl << "=== End of tests ===" << std::endl;
	return 0;
}
