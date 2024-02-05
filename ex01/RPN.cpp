#include "RPN.hpp"

int RPN::calculateRPN(std::string const& rpnExpression)
{
	std::stack<int> operandStack;
	std::istringstream iss(rpnExpression);
	std::string token;
	while (iss >> token)
	{
		if (isOperator(token))
		{
			if (operandStack.size() < 2)
				throw std::runtime_error("Not enough operands for operator: " + token);
			int operand2 = operandStack.top();
			operandStack.pop();
			int operand1 = operandStack.top();
			operandStack.pop();
			int result = performOperation(operand1, operand2, token);
			operandStack.push(result);
		}
		else
			operandStack.push(std::atoi(token.c_str()));
	}
	if (operandStack.size() != 1)
		throw std::runtime_error("Invalid expression");
	return operandStack.top();
}

bool RPN::isOperator(std::string const& token)
{
	return (token == "+" || token == "-" || token == "*" || token == "/");
}

int RPN::performOperation(int operand1, int operand2, std::string const& op)
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
