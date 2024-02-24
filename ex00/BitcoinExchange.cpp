#include "BitcoinExchange.hpp"

void BitcoinExchange::processInputfile(std::string const& inputFilename)
{
	std::ifstream inputFile(inputFilename.c_str());
	if (!inputFile.is_open())
	{
		std::cerr << "Error: File '" << inputFilename << "' not found" << std::endl;
		// error handling
	}
	std::string line;
	while (std::getline(inputFile, line))
	{
		if (line.find("date | value") != std::string::npos)
			continue ;
	}
	std::istringstream iss(line);
	std::string dateStr, valueStr;
	std::getline(iss, dateStr, '|');
	std::getline(iss >> std::ws, valueStr);
	std::string const& bitcoinPricesFilename = "data.csv";
	try
	{
		std::map<std::string, double> bitcoinPrices = BitcoinExchange::readBitcoinPrices(bitcoinPricesFilename);
		std::string closestDate = BitcoinExchange::findClosestDate(dateStr, bitcoinPricesFilename);
		CompareDates compare(std::atoi(closestDate.c_str()));
		std::map<std::string, double>::iterator exchangeRate = std::min_element(bitcoinPrices.begin(), bitcoinPrices.end(), compare);

		if (exchangeRate != bitcoinPrices.end())
		{
			double result = std::atof(valueStr.c_str()) * exchangeRate->second;
			std::cout << " => " << valueStr << " = " << std::fixed << std::setprecision(2) << result << std::endl;
		}
		else
			std::cerr << "Error: Exchange rate not found for date " << dateStr << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

std::map<std::string, double> BitcoinExchange::readBitcoinPrices(std::string const& bitcoinPricesFilename)
{
	std::map<std::string, double> bitcoinPrices;
	std::ifstream file(bitcoinPricesFilename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: Bitcoin prices database not found." << std::endl;
		// error handling
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
			// error handling
		}
	}
	return bitcoinPrices;
}

std::string BitcoinExchange::findClosestDate(std::string const& targetDate, std::string const& bitcoinPricesFilename)
{
	int targetDateTime = std::atoi(targetDate.c_str());
	std::map<std::string, double> bitcoinPrices = readBitcoinPrices(bitcoinPricesFilename);
	CompareDates compare(targetDateTime);
	std::map<std::string, double>::iterator closestDate = std::min_element(bitcoinPrices.begin(), bitcoinPrices.end(), compare);
	return closestDate->first;
}

BitcoinExchange::BitcoinExchange()
{
	std::cout << GREEN << "BitcoinExchange: " << "Default constructor called" << RESET << std::endl;
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
		*this = other;
	}
	return (*this);		
}
