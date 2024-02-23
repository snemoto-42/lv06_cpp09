#include "RPN.hpp"

double RPN::calculateRPN(std::string const& rpnExpression)
{
	std::stack<double> operandStack;
	std::istringstream iss(rpnExpression);
	std::string token;
	while (iss >> token)
	{
		if (isOperator(token))
		{
			if (operandStack.size() < 2)
				throw std::runtime_error("Not enough operands for operator: " + token);
			double operand2 = operandStack.top();
			operandStack.pop();
			double operand1 = operandStack.top();
			operandStack.pop();
			double result = performOperation(operand1, operand2, token);
			operandStack.push(result);
		}
		else if (token.find_first_not_of(".0123456789") != std::string::npos)
			throw std::runtime_error("Args will always be number or operator");
		else if (std::atof(token.c_str()) >= 10)
			throw std::runtime_error("Nummbers will always be less than 10");
		else
			operandStack.push(std::atof(token.c_str()));
	}
	if (operandStack.size() != 1)
		throw std::runtime_error("Invalid expression");
	return operandStack.top();
}

bool RPN::isOperator(std::string const& token)
{
	return (token == "+" || token == "-" || token == "*" || token == "/");
}

double RPN::performOperation(double operand1, double operand2, std::string const& op)
{
	if (op == "+")
	{
		return operand1 + operand2;
	}
	else if (op == "-")
	{
		return operand1 - operand2;
	}
	else if (op == "*")
	{
		return operand1 * operand2;
	}
	else if (op == "/")
	{
		if (operand2 == 0)
			throw std::runtime_error("Division by zero");
		return operand1 / operand2;
	}
	else
		throw std::runtime_error("Invalid operator: " + op);
}

RPN::RPN()
{
	std::cout << GREEN << "Default constructor called" << RESET << std::endl;
}

RPN::~RPN()
{
	std::cout << GREEN << "Destructor called" << RESET << std::endl;	
}

RPN::RPN(RPN const& x)
{
	std::cout << GREEN << "Copy constructor called" << RESET << std::endl;
	*this = x;
}

RPN& RPN::operator=(RPN const& x)
{
	std::cout << GREEN << "Copy assignment operator called" << RESET << std::endl;
	if (this != &x)
	{
		*this = x;
	}
	return (*this);		
}
