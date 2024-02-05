#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Invalid arg" << std::endl;
		return 1;
	}
	try
	{
		PmergeMe::processSequence(argc - 1, argv + 1);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}	
	return 0;
}
