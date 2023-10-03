/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:06:29 by khorike           #+#    #+#             */
/*   Updated: 2023/09/29 16:13:30 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac, char *av[])
{
	if (ac != 2)
	{
		std::cerr << RED << "Usage: " <<  av[0] << " <input-file>" << END << std::endl;
		return 1;
	}

	// test
	BitcoinPriceDatabase db;
	db.load("date.csv");
	// db.load("date_mini.csv");

	// error csv data
	// db.load("invaild_ver/invaild_data_csv/iv_1_1_empty.csv");
	// db.load("invaild_ver/invaild_data_csv/iv_1_2_space.csv");
	// db.load("invaild_ver/invaild_data_csv/iv_2_1_set_error.csv");
	// db.load("invaild_ver/invaild_data_csv/iv_2_2_format_err.csv");
	// db.load("invaild_ver/invaild_data_csv/iv_3_1_1999_ago.csv");
	// db.load("invaild_ver/invaild_data_csv/iv_3_2_2101_next.csv");
	// db.load("invaild_ver/invaild_data_csv/iv_3_3_leeap_year_.csv");
	// db.load("invaild_ver/invaild_data_csv/iv_3_4_wrong_month_day.csv");

	// error csv float
	// db.load("invaild_ver/invaild_float_csv/iv_f_1_f<0_||1000<f.csv");
	
	
	// db.printData();
	db.processInputFile(av[1]);
	// std::ifstream input_file(av[1]);
	
	return 0;
}
