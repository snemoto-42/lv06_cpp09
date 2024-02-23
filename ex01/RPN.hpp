#pragma once

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"

#include <iostream>
#include <sstream>
#include <stack>

class RPN
{
	public:
		static double calculateRPN(std::string const&);

	private:
		static bool isOperator(std::string const&);
		static double performOperation(double, double, std::string const&);

		RPN();
		~RPN();
		RPN(RPN const&);
		RPN & operator=(RPN const&);
}; 
