#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <exception>
#include <map>
#include <string>

// The database is kept in a std::map: it stays sorted by date, which is what
// makes "the closest earlier date" a single lower_bound away.

class BitcoinExchange {
private:
	std::map<std::string, double>	rates;

public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	void	loadDatabase(const std::string& path);
	void	processInput(const std::string& path) const;

	double	getRateAt(const std::string& date) const;

	class FileException : public std::exception {
	public:
		virtual const char*	what() const throw();
	};

	class NoRateException : public std::exception {
	public:
		virtual const char*	what() const throw();
	};
};

#endif
