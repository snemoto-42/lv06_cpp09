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
		static int calculateRPN(std::string const&);

	private:
		static bool isOperator(std::string const&);
		static int performOperation(int, int, std::string const&);
}; 
