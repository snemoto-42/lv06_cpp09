#pragma once

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct BitcoinData
{
	std::string date;
	double value;
};

class CompareDates
{
	public:
		explicit CompareDates(int targetDateTime): _targetDateTime(targetDateTime){}
		bool operator()(BitcoinData const& a, BitcoinData const& b) const
		{
			return std::abs(std::atoi(a.date.c_str()) - _targetDateTime) < std::abs(std::atoi(b.date.c_str()) - _targetDateTime);
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

		std::vector<BitcoinData> readBitcoinPrices(void);
		std::string findClosestDate(std::string const&);	

	private:
		std::string _bitcoinPricesFilename;
		BitcoinExchange();
}; 
