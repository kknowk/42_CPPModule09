/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:06:27 by khorike           #+#    #+#             */
/*   Updated: 2023/09/30 13:52:10 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN& other) {(void)&other; }

RPN::~RPN() {}

RPN& RPN::operator=(const RPN& other)
{
	(void)&other;
	return *this;
}


bool RPN::isOperator(const std::string& token)
{
	return token == "+" || token == "-" || token == "*" || token == "/";
}

int RPN::performOperation(int a, int b, const std::string& op)
{
	// INT_MIN INT_MAX が計算の途中に超えたらエラー
	if(op == "+")
	{
		if(a > 0 && b > std::numeric_limits<int>::max() - a)
			throw std::overflow_error("Addition overflow");
		if(a < 0 && b < std::numeric_limits<int>::min() - a)
			throw std::overflow_error("Addition underflow");
		return a + b;
	}
	if(op == "-")
	{
		if(a > 0 && b < a - std::numeric_limits<int>::max())
			throw std::overflow_error("Subtraction overflow");
		if(a < 0 && b > a - std::numeric_limits<int>::min())
			throw std::overflow_error("Subtraction underflow");
		return a - b;
	}
	if(op == "*")
	{
		if(a > std::numeric_limits<int>::max() / b)
			throw std::overflow_error("Multiplication overflow");
		if(a < std::numeric_limits<int>::min() / b)
			throw std::overflow_error("Multiplication underflow");
		return a * b;
	}
	if(op == "/" && b != 0)
	{
		if(a == std::numeric_limits<int>::min() && b == -1)
			throw std::overflow_error("Division overflow");
		return a / b;
	}
	std::cout << RED << "Error: Invalid operation or division by zero." << END << std::endl;
	exit(EXIT_FAILURE);
}

int RPN::evaluate(const std::string& expression)
{
	std::istringstream iss(expression);
	std::string token;
	std::stack<int> operands;

	while (iss >> token)
	{
		if (isOperator(token))
		{
			if (operands.size() < 2)
			{
				std::cout << RED << "Error: Insufficient operands." << END << std::endl;
				exit(EXIT_FAILURE);
			}
			int b = operands.top();
			operands.pop();
			int a = operands.top();
			operands.pop();
			try {
				operands.push(performOperation(a, b, token));
			} catch (const std::exception& e) {
				std::cerr << e.what() << std::endl;
				std::exit(EXIT_FAILURE);
			}
		}
		else
		{
			std::istringstream tokenStream(token);
			int value;
			// 数字のみで構成されているか
			if (tokenStream >> value && tokenStream.eof())
			{
				operands.push(value);
			}
			else
			{
				std::cout << RED << "Error: Invalid token '" << token << "'." << END << std::endl;
				exit(EXIT_FAILURE);
			}
		}
	}
	if (operands.size() != 1)
	{
		std::cout << RED << "Error: Invalid expression." << END << std::endl;
		exit(EXIT_FAILURE);
	}
	return operands.top();
}
