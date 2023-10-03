/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:06:25 by khorike           #+#    #+#             */
/*   Updated: 2023/09/29 16:19:22 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BITCOINEXCHANGE_HPP
#define  BITCOINEXCHANGE_HPP

#include <fstream>
#include <cmath>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>

// コンテナ
#include <map>


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

// success failure EXIT
#define FAILURE 1
#define SUCCESS 0


class BitcoinPriceDatabase {
public:

	BitcoinPriceDatabase();
	BitcoinPriceDatabase(const BitcoinPriceDatabase& other);
	~BitcoinPriceDatabase();
	BitcoinPriceDatabase& operator=(const BitcoinPriceDatabase& other);

	void load(const std::string& filename);

	void printData() const;
	
	
	float getExchangeRate(const std::string& date);
	void processInputFile(const std::string& filename);
	

private:
	int validateDate(const std::string& date);
	int validateFloat(const float exchangeRate, int flag);
	std::map<std::string, float> data_;
};

#endif


// std::map<std::string, float>
// std::stringはキーの型　floatは値の型

// data_のような末尾にアンダースコアを持つ名前は、
// 通常、プライベートメンバ変数を示すために使用される。