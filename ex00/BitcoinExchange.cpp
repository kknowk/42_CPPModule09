/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:06:27 by khorike           #+#    #+#             */
/*   Updated: 2023/10/02 14:36:38 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinPriceDatabase::BitcoinPriceDatabase() {}

BitcoinPriceDatabase::BitcoinPriceDatabase(const BitcoinPriceDatabase& other) : data_(other.data_) {}

BitcoinPriceDatabase::~BitcoinPriceDatabase() {}

BitcoinPriceDatabase& BitcoinPriceDatabase::operator=(const BitcoinPriceDatabase& other)
{
	if (this != &other)
		data_ = other.data_;
	return *this;
}

int BitcoinPriceDatabase::validateDate(const std::string& date)
{
	std::istringstream iss(date);
	char delimiter;
	int year, month, day;
	
	if (iss >> year >> delimiter >> month >> delimiter >> day && delimiter == '-')
	{
		// std::cout << year<< "  " << month << "  " << day << std::endl;
		// 前提チェック
		// ちなみにビットコインは2008からできたらしい
		if (!(year >= 2000 && year <= 2100 && month >= 1 && month <= 12 && day >= 1 && day <= 31))
		{
			
			std::cerr << RED << "Error: Invalid date " << date << END << std::endl;
			return FAILURE;
		}

		// 閏年のチェック
		bool isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));

		// 月の日数をチェック
		bool isValid = false;
		if ((month == 4 || month == 6 || month == 9 || month == 11) && day <= 30)
		{
			// 4, 6, 9, 11月は30日まで
			isValid = true;
		}
		else if (month == 2)
		{
			// 2月は閏年であれば29日まで、それ以外は28日まで
			isValid = (isLeapYear && day <= 29) || (!isLeapYear && day <= 28);
		}
		else if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) &&day <= 31)
		{
			// それ以外の月は31日まで
			isValid = true;
		}
		if (!isValid)
		{
			std::cerr << RED << "Error: Invalid date " << date << END << std::endl;
			return FAILURE;
		}
		return SUCCESS;
	}
	std::cerr << RED << "Error: Invalid argument " << END << std::endl;
	return FAILURE;
}

int BitcoinPriceDatabase::validateFloat(const float exchangeRate, int flag)
{
	// exchangeRateを100倍して整数に丸め、再び100で割って元の値に戻す
	if (exchangeRate != 0)
	{
		float roundedExchangeRate = roundf(exchangeRate * 100) / 100;

		// 元の値と丸められた値が異なる場合、小数点以下2桁以上の値が存在する
		if (exchangeRate != roundedExchangeRate)
		{
			std::cerr << RED << "Error: Exchange rate has more than two decimal places => " << END << exchangeRate << std::endl;
			return FAILURE;
		}
	}
	// exchangeRateが0から1000の範囲内にあるか確認
	if (exchangeRate < 0)
	{
		std::cerr << RED << "Error: not a positive number. " << END << std::endl;
		return FAILURE;
	}
	if (exchangeRate > 1000 && flag == SUCCESS)
	{
		std::cerr << RED << "Error: too large a number." << END << std::endl;
		return FAILURE;
	}
	return SUCCESS;
}

void BitcoinPriceDatabase::load(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cerr << RED << "Error: could not open file " << END << std::endl;
		std::exit(EXIT_FAILURE);
	}

	std::string line;

	// 最初の一行はフォーマットだから空うち
	// 空っぽならエラー
	if (std::getline(file, line).eof())
	{
		std::cerr << RED << "Error: file empty or no data in. " << END << std::endl;
		std::exit(EXIT_FAILURE);
	}
	
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::string date;
		std::string exchangeRateStr;
		
		std::getline(iss, date, ',');

		if (validateDate(date))
		{
			// std::exit(EXIT_FAILURE);
			;
		}

		std::getline(iss, exchangeRateStr, ',');

		// check contents
		// std::cout << date << std::endl;
		
		std::istringstream exchangeRateStream(exchangeRateStr);

		// 1000,00 までを許容する
		if (exchangeRateStr.size() > 8)
		{
			std::cerr << RED << "Error: bad exchange rate => " << line << END << std::endl;
			std::exit(EXIT_FAILURE);
		}
		float exchangeRate;
		if (!(exchangeRateStream >> exchangeRate))
		{
			std::cerr << RED << "Error: bad exchange rate => " << line << END << std::endl;
			std::exit(EXIT_FAILURE);
		}
		else
		{
			// float check
			if (validateFloat(exchangeRate, FAILURE))
			{
				// std::exit(EXIT_FAILURE);
				;
			}
			// Mapにデータを保存
			data_[date] = exchangeRate;
		}
	}
	file.close();
}

// Mapのデータを確認
void BitcoinPriceDatabase::printData() const
{
	for (std::map<std::string, float>::const_iterator it = data_.begin(); it != data_.end(); ++it)
		std::cout << it->first << ": " << it->second << std::endl;
}

float BitcoinPriceDatabase::getExchangeRate(const std::string& date)
{
	std::map<std::string, float>::iterator it = data_.find(date);
	if (it != data_.end())
	{
		// 日付がマップに存在する場合、対応する交換レートを返す
		// first が日付
		return it->second;
	}
	else
	{
		// 日付がマップに存在しない場合、最も近い過去の日付の交換レートを検索
		// 指定された要素以上の値が現れる最初の位置のイテレータを取得する
		it = data_.lower_bound(date);
		if (it != data_.begin())
		{
			--it;  // 最も近い過去の日付に対するイテレータに戻る
			return it->second;  // 最も近い過去の日付の交換レートを返す
		}
		else
		{
			// 最も近い過去の日付が見つからない場合、先頭
			return it->second;
		}
	}
}

void BitcoinPriceDatabase::processInputFile(const std::string& filename)
{
	std::ifstream input_file(filename);
	if (!input_file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		std::exit(EXIT_FAILURE);
	}
	std::string line;
	
	// 最初の一行はフォーマットだから空うち
	// 空っぽならエラー
	if (std::getline(input_file, line).eof())
	{
		std::cerr << RED << "Error: file empty or no data in. " << END << std::endl;
		std::exit(EXIT_FAILURE);
	}

	while (std::getline(input_file, line))
	{
		std::istringstream iss(line);
		std::string date;
		std::string exchangeRate;
		char delimiter;
		int flag = 0;
		if (iss >> date >> delimiter >> exchangeRate && delimiter == '|')
		{
			if (validateDate(date))
			{
				flag = 1;
			}
			std::istringstream exchangeRateStream(exchangeRate);
			// 1000,00 までを許容する
			if (exchangeRate.size() > 8)
			{
				std::cerr << RED << "Error: bad exchange rate => " << line << END << std::endl;
				flag = 1;
			}
			float value;
			if (!(exchangeRateStream >> value))
			{
				std::cerr << RED << "Error: bad exchange rate => " << line << END << std::endl;
				flag = 1;
			}
			else
			{
				if (validateFloat(value, SUCCESS))
				{
					flag = 1;
				}
			}
			if (value >= 0 && value <= 1000)
			{
				float exchange_rate = getExchangeRate(date);
				std::cout << GREEN << date << " => " << value << " = " << value * exchange_rate << END << std::endl;
			}
		}
		else if (flag == 0)
			std::cerr << RED << "Error: bad input => " << line << END << std::endl;
	}
	input_file.close();
}