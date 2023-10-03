/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:06:25 by khorike           #+#    #+#             */
/*   Updated: 2023/10/02 21:20:44 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PMERGEME_HPP
#define  PMERGEME_HPP

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <sys/time.h>
#include <iomanip> 
#include <ctime>  // 処理時間を計測するため

// コンテナ
// #include <deque>
#include <list>
#include <vector>


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

// vector

class VectorMergeInsertSorter {
public:
	
	VectorMergeInsertSorter();
	VectorMergeInsertSorter(const VectorMergeInsertSorter& other);
	~VectorMergeInsertSorter();
	VectorMergeInsertSorter& operator=(const VectorMergeInsertSorter& other);

	VectorMergeInsertSorter(const std::vector<int>& vec);
	void vec_sort();
	void vec_printArray();
	void vec_printDuration();

private:
	std::vector<int> arr;
	double vec_duration; // ソートの処理時間を保存

	void vec_div_group(std::vector<int>& input, std::vector<int>& largeElements, std::vector<int>& smallElements);
	void vec_mergeSorter(std::vector<int>& input, int left, int right);

	void vec_insertionSort(std::vector<int>& sorted, const std::vector<int>& toInsert);
	void vec_merge(std::vector<int>& merged, const std::vector<int>& leftElements, const std::vector<int>& rightElements, int left, int mid, int right);
};

// list

class ListMergeInsertSorter {
public:

	ListMergeInsertSorter();
	ListMergeInsertSorter(const ListMergeInsertSorter& other);
	~ListMergeInsertSorter();
	ListMergeInsertSorter& operator=(const ListMergeInsertSorter& other);

	ListMergeInsertSorter(const std::list<int>& lst);

	void lst_sort();
	void lst_printList();
	void lst_printDuration();

private:
	std::list<int> lst;
	double lst_duration;

	// void lst_insertionSort(std::list<int>::iterator left, std::list<int>::iterator right);
	// void lst_merge(std::list<int>::iterator left, std::list<int>::iterator mid, std::list<int>::iterator right);
	void lst_div_group(std::list<int>& input, std::list<int>& largeElements, std::list<int>& smallElements);
	void lst_mergeSorter(std::list<int>& input, std::list<int>::iterator left, std::list<int>::iterator right);

	void lst_insertionSort(std::list<int>& sorted, const std::list<int>& toInsert);
	void lst_merge(std::list<int>& input,std::list<int>::iterator leftBegin, std::list<int>::iterator leftEnd,std::list<int>::iterator rightBegin, std::list<int>::iterator rightEnd);
};

#endif
