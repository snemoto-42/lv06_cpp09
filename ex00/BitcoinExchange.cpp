#include "BitcoinExchange.hpp"

void BitcoinExchange::processInputfile(std::string const& inputFilename)
{
	std::string const& bitcoinPricesFilename = "data.csv";
	std::map<std::string, double> bitcoinPrices;
	try
	{
		bitcoinPrices = BitcoinExchange::readBitcoinPrices(bitcoinPricesFilename);
	}
	catch (std::exception const& e)
	{
		std::cerr << e.what() << std::endl;
		return ;
	}
	// for (std::map<std::string, double>::const_iterator it = bitcoinPrices.begin(); it != bitcoinPrices.end(); ++it)
	// {
	// 	std::cout << "\"" << it->first << "\"" << it->second << "\"" << std::endl;
	// }
	std::ifstream inputFile(inputFilename.c_str());
	if (!inputFile.is_open())
	{
		std::cerr << "Error: File '" << inputFilename << "' not found" << std::endl;
		return ;
	}
	std::string line;
	while (std::getline(inputFile, line))
	{
		if (line.find_first_not_of(" |-.0123456789") != std::string::npos)
			continue ;
		std::pair<std::string, double> inputData;
		try
		{
			inputData = BitcoinExchange::readInputfile(line);
			// std::cout << "\"" << inputData.first << "\"" << inputData.second << "\"" << std::endl;
		}
		catch (std::exception const& e)
		{
			std::cerr << e.what() << std::endl;
			continue ;
		}
		std::map<std::string, double>::iterator closestDate;
		try
		{
			closestDate = BitcoinExchange::findClosestDate(inputData.first, bitcoinPrices);
		}
		catch (std::invalid_argument const& e)
		{
			std::cerr << e.what() << std::endl;
		}
		if (closestDate != bitcoinPrices.end())
		{
			double result = inputData.second * closestDate->second;
			std::cout << inputData.first << " => " << inputData.second << " = " << std::fixed << std::setprecision(2) << result << std::endl;
		}
		else
			std::cerr << "Error: Exchange rate not found for date " << inputData.first << std::endl;
	}
}

bool BitcoinExchange::invalidDate(std::string const& date)
{
	int year, month, day;
	char delim;
	std::istringstream dateStream(date);
	if (!(dateStream >> year >> delim >> month >> delim >> day) || delim != '-')
		return true;
	if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
		return true;
	if (month == 2)
	{
		//西暦年号が4で割り切れる年をうるう年とする
		if (year % 4 != 0 && day == 29)
			return true;
		else if (day > 29)
			return true;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)
		if (day == 31)
			return true;
	return false;
}

std::map<std::string, double>::iterator BitcoinExchange::findClosestDate(std::string const& targetDate, std::map<std::string, double> & bitcoinPrices)
{
	std::map<std::string, double>::iterator closestDate = bitcoinPrices.lower_bound(targetDate);
	if (closestDate == bitcoinPrices.begin())
		return closestDate;
	if (closestDate == bitcoinPrices.end())
		std::advance(closestDate, -1);
	else if (closestDate->first != targetDate)
		std::advance(closestDate, -1);
	return closestDate;
}

std::pair<std::string, double> BitcoinExchange::readInputfile(std::string const& line)
{
	std::istringstream iss(line);
	std::string dateStr, valueStr;
	std::string delim = "|";
	if (!(iss >> dateStr >> delim >> valueStr))
		throw std::invalid_argument("Error: Invalid format in the Inputfile.");
	double value = std::atof(valueStr.c_str());
	if (value == 0 && valueStr != "0")
		throw std::invalid_argument("Error: Invalid value in the Inputfile.");
	if (std::atof(valueStr.c_str()) < 0)
		throw std::invalid_argument("Error: not a positive number.");
	if (std::atof(valueStr.c_str()) > 1000)
		throw std::invalid_argument("Error: too large a number.");
	if (invalidDate(dateStr))
	{
		std::ostringstream oss;
		oss << "Error: bad input => " << dateStr;
		throw std::invalid_argument(oss.str());
	}
	std::pair<std::string, double> inputData = std::make_pair(dateStr, value);
	return inputData;
}

std::map<std::string, double> BitcoinExchange::readBitcoinPrices(std::string const& bitcoinPricesFilename)
{
	std::map<std::string, double> bitcoinPrices;
	std::ifstream file(bitcoinPricesFilename.c_str());
	if (!file.is_open())
	{
		throw std::invalid_argument("Error: Bitcoin prices database not found.");
	}
	std::string line;
	while (std::getline(file, line))
	{
		if (line.find_first_not_of("-.,0123456789") != std::string::npos)
			continue ;
		std::istringstream iss(line);
		std::string dateStr, valueStr;
		std::getline(iss, dateStr, ',');
		std::getline(iss, valueStr);
		double value = std::atof(valueStr.c_str());
		if (value == 0 && valueStr != "0")
			throw std::invalid_argument("Error: Invalid value in the Inputfile.");
		bitcoinPrices.insert(std::make_pair(dateStr, value));
	}
	return bitcoinPrices;
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
