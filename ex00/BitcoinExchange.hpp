#pragma once

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

// struct BitcoinData
// {
// 	std::string date;
// 	double value;
// };

class CompareDates
{
	public:
		explicit CompareDates(int targetDateTime): _targetDateTime(targetDateTime){}
		bool operator()(std::pair<std::string, double> const& a, std::pair<std::string, double> const& b) const
		{
			return std::abs(std::atoi(a.first.c_str()) - _targetDateTime) < std::abs(std::atoi(b.first.c_str()) - _targetDateTime);
		}
	private:
		int _targetDateTime;
};

class BitcoinExchange
{
	public:
		BitcoinExchange(std::string const&);
		~BitcoinExchange();
		BitcoinExchange(BitcoinExchange const&);
		BitcoinExchange & operator=(BitcoinExchange const&);

		std::map<std::string, double> readBitcoinPrices(void);
		std::string findClosestDate(std::string const&);	

	private:
		std::string _bitcoinPricesFilename;
		BitcoinExchange();
}; 
