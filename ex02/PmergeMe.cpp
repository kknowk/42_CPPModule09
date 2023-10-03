/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:06:27 by khorike           #+#    #+#             */
/*   Updated: 2023/10/03 12:42:30 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// vector

VectorMergeInsertSorter::VectorMergeInsertSorter() : arr(), vec_duration(0) {}

VectorMergeInsertSorter::VectorMergeInsertSorter(const VectorMergeInsertSorter& other) : arr(other.arr), vec_duration(other.vec_duration) {}

VectorMergeInsertSorter::~VectorMergeInsertSorter() {}

VectorMergeInsertSorter& VectorMergeInsertSorter::operator=(const VectorMergeInsertSorter& other)
{
	if (this != &other)
	{
		arr = other.arr;
		vec_duration = other.vec_duration;
	}
	return *this;
}

VectorMergeInsertSorter::VectorMergeInsertSorter(const std::vector<int>& vec) : arr(vec), vec_duration(0) {}

// まずはinsertsort
// C言語での例はwikiに乗っている
void VectorMergeInsertSorter::vec_insertionSort(std::vector<int>& sorted, const std::vector<int>& toInsert)
{
	// 各要素に対して
	for (size_t i = 0; i < toInsert.size(); ++i)
	{
		int val = toInsert[i];
		// 正しい位置を見つけて挿入する
		std::vector<int>::iterator it = std::lower_bound(sorted.begin(), sorted.end(), val);
		sorted.insert(it, val);
	}
}

// 2つのソート済み配列をマージする関数
// これもwikiにC言語での例が乗っている
void VectorMergeInsertSorter::vec_merge(std::vector<int>& merged, const std::vector<int>& leftElements, const std::vector<int>& rightElements, int left, int mid, int right)
{
	int i = 0;  // leftElementsのインデックス
	int j = 0;  // rightElementsのインデックス
	int k = left;  // mergedのインデックス

	while (i < mid - left && j < right - mid)
	{
		if (leftElements[i] <= rightElements[j])
			merged[k++] = leftElements[i++];
		else
			merged[k++] = rightElements[j++];
	}

	while (i < mid - left)
		merged[k++] = leftElements[i++];

	while (j < right - mid)
		merged[k++] = rightElements[j++];
}

// 大きい方を格納する
void VectorMergeInsertSorter::vec_div_group(std::vector<int>& input, std::vector<int>& largeElements, std::vector<int>& smallElements)
{
	int n = input.size();
	if (n <= 1)
		return;
	for (int i = 0; i < n - 1; i += 2)
	{
		if (input[i] > input[i + 1])
		{
			largeElements.push_back(input[i]);
			smallElements.push_back(input[i + 1]);
		}
		else
		{
			largeElements.push_back(input[i + 1]);
			smallElements.push_back(input[i]);
		}
	}
	// 奇数
	if (n % 2 == 1)
		largeElements.push_back(input[n - 1]);
	return;
}

// 再帰的に大きい方をソートする
void VectorMergeInsertSorter::vec_mergeSorter(std::vector<int>& input, int left, int right)
{
	if (right - left <= 1)
		return;  // 再帰の基本ケース: サイズが1以下の場合

	int mid = (left + right) / 2;
	std::vector<int> leftElements(input.begin() + left, input.begin() + mid);
	std::vector<int> rightElements(input.begin() + mid, input.begin() + right);

	// 再帰的にソート
	vec_mergeSorter(leftElements, 0, mid - left);
	vec_mergeSorter(rightElements, 0, right - mid);

	// mergedベクタを作成し、マージ
	std::vector<int> merged(right - left);
	vec_merge(merged, leftElements, rightElements, 0, mid - left, right - left);

	// inputベクタを更新
	std::copy(merged.begin(), merged.end(), input.begin() + left);
}

void VectorMergeInsertSorter::vec_sort()
{
	clock_t start = clock();

	if (arr.size() <= 1)
		return;
	std::vector<int> largeElements;
	std::vector<int> smallElements;
	vec_div_group(arr, largeElements, smallElements);
	vec_mergeSorter(smallElements, 0, smallElements.size());

	vec_insertionSort(smallElements, largeElements);
	arr.assign(smallElements.begin(), smallElements.end());
	clock_t end = clock();

	vec_duration  = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;   // ms
}

void VectorMergeInsertSorter::vec_printArray()
{
	for (size_t i = 0; i < arr.size(); ++i)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
}

void VectorMergeInsertSorter::vec_printDuration()
{
	std::cout << "Time to process a range of " << std::right << std::setw(3) << arr.size() << " elements " << "with std::vector : " << vec_duration << " ms" << std::endl;
}


// list


ListMergeInsertSorter::ListMergeInsertSorter() : lst(), lst_duration(0) {}

ListMergeInsertSorter::ListMergeInsertSorter(const ListMergeInsertSorter& other) : lst(other.lst), lst_duration(other.lst_duration) {}

ListMergeInsertSorter::~ListMergeInsertSorter() {}

ListMergeInsertSorter& ListMergeInsertSorter::operator=(const ListMergeInsertSorter& other)
{
	if (this != &other)
	{
		lst = other.lst;
		lst_duration = other.lst_duration;
	}
	return *this;
}

ListMergeInsertSorter::ListMergeInsertSorter(const std::list<int>& lst) : lst(lst), lst_duration(0) {}


void ListMergeInsertSorter::lst_div_group(std::list<int>& input, std::list<int>& largeElements, std::list<int>& smallElements)
{
	int n = input.size();
	if (n <= 1)
		return;

	std::list<int>::iterator it = input.begin();
	for (int i = 0; i < n - 1; i += 2)
	{
		// 最初の要素
		int val1 = *it; ++it;
		// その次の要素
		int val2 = *it; ++it;

		if (val1 > val2)
		{
			largeElements.push_back(val1);
			smallElements.push_back(val2);
		}
		else
		{
			largeElements.push_back(val2);
			smallElements.push_back(val1);
		}
	}
	// 奇数
	if (n % 2 == 1)
		largeElements.push_back(*it);
}

void ListMergeInsertSorter::lst_merge(std::list<int>& input,
			std::list<int>::iterator leftBegin, std::list<int>::iterator leftEnd,
			std::list<int>::iterator rightBegin, std::list<int>::iterator rightEnd)
{
	std::list<int>::iterator it1 = leftBegin;
	std::list<int>::iterator it2 = rightBegin;
	while (it1 != leftEnd && it2 != rightEnd)
	{
		if (*it1 <= *it2)
		{
			input.push_back(*it1);
			++it1;
		}
		else
		{
			input.push_back(*it2);
			++it2;
		}
	}
	while (it1 != leftEnd)
	{
		input.push_back(*it1);
		++it1;
	}
	while (it2 != rightEnd)
	{
		input.push_back(*it2);
		++it2;
	}
}


void ListMergeInsertSorter::lst_mergeSorter(std::list<int>& input, std::list<int>::iterator left, std::list<int>::iterator right)
{
	if (std::distance(left, right) <= 1)
		return;  // Base case: size is 1 or 0

	std::list<int>::iterator mid = left;
	std::advance(mid, std::distance(left, right) / 2);

	std::list<int> leftElements;
	std::list<int> rightElements;

	leftElements.splice(leftElements.begin(), input, left, mid);
	rightElements.splice(rightElements.begin(), input, mid, right);

	// Recursively sort
	lst_mergeSorter(leftElements, leftElements.begin(), leftElements.end());
	lst_mergeSorter(rightElements, rightElements.begin(), rightElements.end());

	// Merge back into input
	lst_merge(input, leftElements.begin(), leftElements.end(), rightElements.begin(), rightElements.end());
}

void ListMergeInsertSorter::lst_insertionSort(std::list<int>& sorted, const std::list<int>& toInsert)
{
	for (std::list<int>::const_iterator it_toInsert = toInsert.begin(); it_toInsert != toInsert.end(); ++it_toInsert)
	{
		int val = *it_toInsert;
		// 正しい位置を見つけて挿入する
		std::list<int>::iterator it_sorted = std::lower_bound(sorted.begin(), sorted.end(), val);
		sorted.insert(it_sorted, val);
	}
}


void ListMergeInsertSorter::lst_sort()
{
	clock_t start = clock();

	int n = std::distance(lst.begin(), lst.end());
	if (n <= 1)
		return;

	std::list<int>::iterator mid = lst.begin();
	
	std::list<int> largeElements;
	std::list<int> smallElements;
	// イテレータをn回進める。
	// つまり真ん中まで持ってくる
	std::advance(mid, n / 2);


	lst_div_group(lst, largeElements, smallElements);
	lst_mergeSorter(smallElements, smallElements.begin(), smallElements.end());
	lst_insertionSort(smallElements, largeElements);
	lst.assign(smallElements.begin(), smallElements.end());

	clock_t end = clock();

	lst_duration = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;   // ms
}

void ListMergeInsertSorter::lst_printList()
{
	for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void ListMergeInsertSorter::lst_printDuration()
{
	std::cout << "Time to process a range of " << std::right << std::setw(3) << lst.size() << " elements " << "with std::list " << "  : "<< lst_duration << " ms" << std::endl;
}
