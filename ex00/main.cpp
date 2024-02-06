#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Invalid arg" << std::endl;
		return 1;
	}
	std::string const inputFilename = argv[1];
	std::string const bitcoinPricesFilename = "data.csv";
	BitcoinExchange exchange(bitcoinPricesFilename);
	std::ifstream inputFile(inputFilename.c_str());
	if (!inputFile.is_open())
	{
		std::cerr << "Error: File '" << inputFilename << "' not found" << std::endl;
		return 1;
	}

	std::string line;
	while (std::getline(inputFile, line))
	{
		if (line.find("date | value") != std::string::npos)
			continue ;
	}

	std::istringstream iss(line);
	std::string dateStr;
	std::string valueStr;
	try
	{
		std::string closestDate = exchange.findClosestDate(dateStr);
		std::map<std::string, double> bitcoinPrices = exchange.readBitcoinPrices();
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
	return 0;
}
