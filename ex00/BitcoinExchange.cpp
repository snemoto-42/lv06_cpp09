#include "BitcoinExchange.hpp"

void BitcoinExchange::processInputfile(std::string const& inputFilename)
{
	std::string const& bitcoinPricesFilename = "data.csv";
	std::map<std::string, double> bitcoinPrices;
	try
	{
		bitcoinPrices = BitcoinExchange::readBitcoinPrices(bitcoinPricesFilename);
	}
	catch (std::invalid_argument const& e)
	{
		std::cerr << e.what() << std::endl;
		// std::cerr << "Error: Invalid value in the Bitcoin prices database." << std::endl;
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
		//完全一致でなくても読み飛ばす？
		if (line.find("date | value") != std::string::npos)
			continue ;
		std::pair<std::string, double> inputData;
		try
		{
			inputData = BitcoinExchange::readInputfile(line);
		}
		catch (std::invalid_argument const& e)
		{
			std::cerr << "Error: Invalid value in the Inputfile." << std::endl;
			continue ;
		}
		if (inputData.second < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue ;
		}
		else if (inputData.second > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue ;
		}
		if (invalidDate(inputData.first))
		{
			std::cerr << "Error: bad input => " << inputData.first << std::endl;
			continue ;
		}
		// std::cout << "\"" << inputData.first << "\"" << inputData.second << "\"" << std::endl;
		std::map<std::string, double>::iterator closestDate = BitcoinExchange::findClosestDate(inputData.first, bitcoinPrices);
		if (closestDate != bitcoinPrices.end())
		{
			double result = inputData.second * closestDate->second;
			std::cout << inputData.first << " => " << inputData.second << " = " << std::fixed << std::setprecision(1) << result << std::endl;
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
	// 月ごとの日数をチェックする追加のロジック
	return false;
}

std::map<std::string, double>::iterator BitcoinExchange::findClosestDate(std::string const& targetDate, std::map<std::string, double> & bitcoinPrices)
{
	//compareクラスを不要にしたい
	int targetDateTime = std::atoi(targetDate.c_str());
	CompareDates compare(targetDateTime);
	std::map<std::string, double>::iterator closestDate = std::min_element(bitcoinPrices.begin(), bitcoinPrices.end(), compare);
	return closestDate;
}

std::pair<std::string, double> BitcoinExchange::readInputfile(std::string const& line)
{
	std::pair<std::string, double> inputData;
	std::istringstream iss(line);
	std::string dateStr, valueStr;
	//データ形式が正しくない
	std::getline(iss, dateStr, '|');
	dateStr.erase(std::remove_if(dateStr.begin(), dateStr.end(), isspace), dateStr.end());
	std::getline(iss, valueStr);

	//throwを返すのか
	inputData = std::make_pair(dateStr, std::atof(valueStr.c_str()));

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
		//完全一致でなくても読み飛ばす？
		if (line.find("date,exchange_rate") != std::string::npos)
			continue ;
		std::istringstream iss(line);
		std::string dateStr, valueStr;
		//データ形式が正しくない
		std::getline(iss, dateStr, ',');
		std::getline(iss, valueStr);

		//throwを返すのか
		bitcoinPrices.insert(std::make_pair(dateStr, std::atof(valueStr.c_str())));
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
