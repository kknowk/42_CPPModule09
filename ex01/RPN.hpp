/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:06:25 by khorike           #+#    #+#             */
/*   Updated: 2023/09/30 13:42:27 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RPN_HPP
#define  RPN_HPP

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <limits>
#include <stdexcept>

// コンテナ
#include <stack>


// color
#define END             "\033[0m"
#define BOLD            "\033[1m"
#define BLACK           "\033[30m"
#define RED             "\033[31m"
#define GREEN           "\033[32m"
#define YELLOW          "\033[33m"
#define BLUE            "\033[34m"
#define MAGENTA         "\033[35m"
#define CYAN            "\033[36m"
#define WHITE           "\033[37m"
#define UNDERLINE       "\033[4m"
#define BOLD_UNDERLINE  "\033[1;4m"

class RPN {
public:

	RPN();
	RPN(const RPN& other);
	~RPN();
	RPN& operator=(const RPN& other);

	int evaluate(const std::string& expression);

private:
	bool isOperator(const std::string& token);
	int performOperation(int a, int b, const std::string& op);
};

#endif
