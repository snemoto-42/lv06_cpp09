#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	std::cout << GREEN << "BitcoinExchange: " << "Default constructor called" << RESET << std::endl;
}

BitcoinExchange::BitcoinExchange(std::string const& bitcoinPricesFilename):_bitcoinPricesFilename(bitcoinPricesFilename)
{
	std::cout << GREEN << "BitcoinExchange: " << "Constructor with argment called" << RESET << std::endl;
}

BitcoinExchange::~BitcoinExchange()
{
	std::cout << GREEN << "BitcoinExchange: " << "Destructor called" << RESET << std::endl;	
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const& other)
{
	std::cout << GREEN << "BitcoinExchange: " << "Copy constructor called" << RESET << std::endl;
	*this = other;
}

BitcoinExchange & BitcoinExchange::operator=(BitcoinExchange const& other)
{
	std::cout << GREEN << "BitcoinExchange: " << "Copy assignment operator called" << RESET << std::endl;
	if (this != &other)
	{
	}
	return (*this);		
}

std::map<std::string, double> BitcoinExchange::readBitcoinPrices(void)
{
	std::map<std::string, double> bitcoinPrices;
	std::ifstream file(_bitcoinPricesFilename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: Bitcoin prices database not found." << std::endl;
		std::exit(1);
	}
	std::string line;
	while (std::getline(file, line))
	{
		if (line.find("data | value") != std::string::npos)
			continue ;
		std::istringstream iss(line);
		std::string dateStr;
		std::string valueStr;
		iss >> dateStr >> valueStr;
		try
		{
			bitcoinPrices.insert(std::make_pair(dateStr, std::atof(valueStr.c_str())));
		}
		catch (std::invalid_argument const& e)
		{
			std::cerr << "Error: Invalid value in the Bitcoin prices database." << std::endl;
			std::exit(1);
		}
	}
	return bitcoinPrices;
}

std::string BitcoinExchange::findClosestDate(std::string const& targetDate)
{
	int targetDateTime = std::atoi(targetDate.c_str());
	std::map<std::string, double> bitcoinPrices = readBitcoinPrices();
	CompareDates compare(targetDateTime);
	std::map<std::string, double>::iterator closestDate = std::min_element(bitcoinPrices.begin(), bitcoinPrices.end(), compare);
	return closestDate->first;
}
