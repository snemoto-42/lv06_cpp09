#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Invalid arg" << std::endl;
		return 1;
	}
	BitcoinExchange::processInputfile(argv[1]);
	return 0;
}
