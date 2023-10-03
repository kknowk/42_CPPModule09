/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:06:29 by khorike           #+#    #+#             */
/*   Updated: 2023/09/30 14:20:25 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

// void	test_Success(RPN calculator)
// {
// 	std::cout << YELLOW << "test Success ver !!!!!!!" << END << std::endl;
// 	std::cout << "------------------------" << std::endl;
	
// 	std::cout << BLUE << "test 1 1 + !!!!!!!" << END << std::endl;
// 	std::cout << GREEN << calculator.evaluate("1 1 +") << END << std::endl;

// 	std::cout << "------------------------" << std::endl;
	
// 	std::cout << BLUE << "test 8 9 * 9 - 9 - 9 - 4 - 1 + !!!!!!!" << END << std::endl;
// 	std::cout << GREEN << calculator.evaluate("8 9 * 9 - 9 - 9 - 4 - 1 +") << END << std::endl;
// 	std::cout << "\n------------------------\n" << std::endl;

// 	std::cout << BLUE << "test 7 7 * 7 - !!!!!!!" << END << std::endl;
// 	std::cout << GREEN << calculator.evaluate("7 7 * 7 -") << END << std::endl;
// 	std::cout << "\n------------------------\n" << std::endl;

// 	std::cout << BLUE << "test 1 2 * 2 / 2 * 2 4 - + !!!!!!!" << END << std::endl;
// 	std::cout << GREEN << calculator.evaluate("1 2 * 2 / 2 * 2 4 - +") << END << std::endl;
	
// 	std::cout << "\n------------------------\n" << std::endl;
// }

// void	test_over_flow(RPN calculator)
// {
// 	std::cout << YELLOW << "test over_flow !!!!!!!" << END << std::endl;
// 	std::cout << "------------------------" << std::endl;
	
// 	// plus
// 	std::cout << BLUE << "test plus max over 2147483647 1 +!!!!!!!" << END << std::endl;
// 	std::cout << GREEN << calculator.evaluate("2147483647 1 +") << END << std::endl;
// 	std::cout << "------------------------" << std::endl;

// 	std::cout << BLUE << "test plus min over -2147483648 -1 +!!!!!!!" << END << std::endl;
// 	std::cout << GREEN << calculator.evaluate("-2147483648 -1 +") << END << std::endl;
	
// 	std::cout << "\n------------------------\n" << std::endl;
	
// 	// minus
// 	std::cout << BLUE << "test minus max over 2147483647 -1 -!!!!!!!" << END << std::endl;
// 	std::cout << GREEN << calculator.evaluate("2147483647 -1 -") << END << std::endl;

// 	std::cout << "\n------------------------\n" << std::endl;

// 	std::cout << BLUE << "test minus min over -2147483648 1 -!!!!!!!" << END << std::endl;
// 	std::cout << GREEN << calculator.evaluate("-2147483648 1 -") << END << std::endl;
	
// 	std::cout << "\n------------------------\n" << std::endl;

// 	// 2147483647 INT_MAX
// 	// 387420489 9^9
// 	// 割ると5.5くらい
// 	// multiplication
// 	std::cout << BLUE << "test mult max over 9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 6 *!!!!!!!" << END << std::endl;
// 	std::cout << GREEN << calculator.evaluate("9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 6 *") << END << std::endl;

// 	std::cout << "\n------------------------\n" << std::endl;
	
// 	std::cout << BLUE << "test mult min over -9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 6 *!!!!!!!" << END << std::endl;
// 	std::cout << GREEN << calculator.evaluate("-9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 6 *") << END << std::endl;

// 	std::cout << "\n------------------------\n" << std::endl;

// 	// division
// 	std::cout << BLUE << "test mivi min over -2147483648 -1 /!!!!!!!" << END << std::endl;
// 	std::cout << GREEN << calculator.evaluate("-2147483648 -1 /") << END << std::endl;

// }

// void	test_invaild(RPN calculator)
// {
// 	std::cout << YELLOW << "test invaild !!!!!!!" << END << std::endl;
// 	std::cout << "------------------------" << std::endl;
	
// 	std::cout << BLUE << "test mix num str 1 a + !!!!!!!" << END << std::endl;
// 	std::cout << GREEN << calculator.evaluate("1 a +") << END << std::endl;
// 	std::cout << "------------------------" << std::endl;
	
// 	std::cout << BLUE << "test only numbers 1 1!!!!!!!" << END << std::endl;
// 	std::cout << GREEN << calculator.evaluate("1 1 ") << END << std::endl;
// 	std::cout << "\n------------------------\n" << std::endl;
	
// 	std::cout << BLUE << "test not enough sign 1 1 + 2!!!!!!!" << END << std::endl;
// 	std::cout << GREEN << calculator.evaluate("1 1 + 2") << END << std::endl;

// 	std::cout << "\n------------------------\n" << std::endl;
	
// 	std::cout << BLUE << "test division by zero 1 0 / !!!!!!!" << END << std::endl;
// 	std::cout << GREEN << calculator.evaluate("1 0 /") << END << std::endl;

// 	std::cout << "\n------------------------\n" << std::endl;
// }

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << RED << "Error: Invalid number of arguments." << END << std::endl;
		return 1;
	}

	RPN calculator;
	std::cout << GREEN << calculator.evaluate(argv[1]) << END << std::endl;
	// (void)argv;
	// test_over_flow(calculator);
	// test_Success(calculator);
	// test_invaild(calculator);
	return 0;
}

