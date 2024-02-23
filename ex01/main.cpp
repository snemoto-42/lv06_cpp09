#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Invalid arg" << std::endl;
		return 1;
	}
	std::string rpnExpression = argv[1];
	try
	{
		double result = RPN::calculateRPN(rpnExpression);
		std::cout << result << std::endl;
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
