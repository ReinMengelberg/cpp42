#include "BitcoinExchange.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

static const double	maxValue = 1000.0;

static std::string	trim(const std::string& text)
{
	const std::string			blanks = " \t\r\n\v\f";
	std::string::size_type		first = text.find_first_not_of(blanks);

	if (first == std::string::npos)
		return "";

	std::string::size_type	last = text.find_last_not_of(blanks);

	return text.substr(first, last - first + 1);
}

static bool	isAllDigits(const std::string& text)
{
	for (std::string::size_type i = 0; i < text.length(); i++)
	{
		if (text[i] < '0' || text[i] > '9')
			return false;
	}
	return !text.empty();
}

static bool	isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

static int	daysInMonth(int year, int month)
{
	static const int	days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (month == 2 && isLeapYear(year))
		return 29;
	return days[month - 1];
}

static bool	isValidDate(const std::string& date)
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	const std::string	yearPart = date.substr(0, 4);
	const std::string	monthPart = date.substr(5, 2);
	const std::string	dayPart = date.substr(8, 2);

	if (!isAllDigits(yearPart) || !isAllDigits(monthPart) || !isAllDigits(dayPart))
		return false;

	const int	year = std::atoi(yearPart.c_str());
	const int	month = std::atoi(monthPart.c_str());
	const int	day = std::atoi(dayPart.c_str());

	if (year < 1 || month < 1 || month > 12)
		return false;
	return day >= 1 && day <= daysInMonth(year, month);
}

static bool	parseNumber(const std::string& text, double& result)
{
	if (text.empty())
		return false;

	std::istringstream	stream(text);
	double				parsed = 0.0;

	stream >> parsed;
	if (stream.fail())
		return false;

	// Nothing but blanks may follow the number.
	std::string	leftover;

	stream >> leftover;
	if (!leftover.empty())
		return false;
	result = parsed;
	return true;
}

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : rates(other.rates)
{
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		rates = other.rates;
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::loadDatabase(const std::string& path)
{
	std::ifstream	file(path.c_str());

	if (!file.is_open())
		throw BitcoinExchange::FileException();

	std::string	line;
	bool		firstLine = true;

	while (std::getline(file, line))
	{
		line = trim(line);
		if (line.empty())
			continue;
		if (firstLine && line == "date,exchange_rate")
		{
			firstLine = false;
			continue;
		}
		firstLine = false;

		const std::string::size_type	separator = line.find(',');

		if (separator == std::string::npos)
			continue;

		const std::string	date = trim(line.substr(0, separator));
		double				rate = 0.0;

		if (!isValidDate(date) || !parseNumber(trim(line.substr(separator + 1)), rate))
			continue;
		rates[date] = rate;
	}
	file.close();
	if (rates.empty())
		throw BitcoinExchange::FileException();
}

// The exact date is used when it exists, otherwise the closest earlier one.
double BitcoinExchange::getRateAt(const std::string& date) const
{
	std::map<std::string, double>::const_iterator	it = rates.lower_bound(date);

	if (it != rates.end() && it->first == date)
		return it->second;
	if (it == rates.begin())
		throw BitcoinExchange::NoRateException();
	--it;
	return it->second;
}

void BitcoinExchange::processInput(const std::string& path) const
{
	std::ifstream	file(path.c_str());

	if (!file.is_open())
		throw BitcoinExchange::FileException();

	std::string	line;
	bool		firstLine = true;

	while (std::getline(file, line))
	{
		line = trim(line);
		if (firstLine)
		{
			firstLine = false;
			if (line == "date | value")
				continue;
		}
		if (line.empty())
			continue;

		const std::string::size_type	separator = line.find('|');

		if (separator == std::string::npos)
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}

		const std::string	date = trim(line.substr(0, separator));
		const std::string	valuePart = trim(line.substr(separator + 1));
		double				value = 0.0;

		if (!isValidDate(date))
		{
			std::cout << "Error: bad input => " << date << std::endl;
			continue;
		}
		if (!parseNumber(valuePart, value))
		{
			std::cout << "Error: bad input => " << valuePart << std::endl;
			continue;
		}
		if (value < 0.0)
		{
			std::cout << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > maxValue)
		{
			std::cout << "Error: too large a number." << std::endl;
			continue;
		}
		try
		{
			// The rate is fetched before anything is printed, so a missing
			// rate does not leave half a line on the output.
			const double	rate = getRateAt(date);

			std::cout << date << " => " << value << " = " << value * rate << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << "Error: " << e.what() << " => " << date << std::endl;
		}
	}
	file.close();
}

const char* BitcoinExchange::FileException::what() const throw()
{
	return "could not open file.";
}

const char* BitcoinExchange::NoRateException::what() const throw()
{
	return "no exchange rate known before this date";
}
