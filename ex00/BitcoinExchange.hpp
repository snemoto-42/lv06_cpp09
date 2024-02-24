#pragma once

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

class BitcoinExchange
{
	public:
		static void processInputfile(std::string const&);
		static std::pair<std::string, double> readInputfile(std::string const&);
		static std::map<std::string, double> readBitcoinPrices(std::string const&);
		static std::map<std::string, double>::iterator findClosestDate(std::string const&, std::map<std::string, double> &);
		static bool invalidDate(std::string const& date);

	private:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(BitcoinExchange const&);
		BitcoinExchange & operator=(BitcoinExchange const&);
}; 
