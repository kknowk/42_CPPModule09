/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:06:29 by khorike           #+#    #+#             */
/*   Updated: 2023/10/03 12:32:34 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"


// brew install coreutils
// shuf は　mac で使えないので gshuf を使う
// コアユーティリティをインストール

int main(int ac, char *av[])
{
	std::vector<int> arr;
	for (int i = 1; i < ac; ++i)
	{
		// basic_istringstreamのエイリアス char 専用
		std::istringstream iss(av[i]);
		int num;
		iss >> num;
		// iss.fail() 入力操作の失敗 検知　INT_MAXなど
		// !iss.eof() 数字で終わっているかどうか 123abc など
		if (iss.fail() || !iss.eof())
		{
			std::cout << RED << "Error: Invalid input '" << av[i] << "'. Please provide a valid integer." << END << std::endl;
			return 1;
		}
		if (num < 0)
		{
			std::cout << RED << "Error: Negative number '" << num << "' encountered. Please provide non-negative integers only." << END << std::endl;
			return 1;
		}
		arr.push_back(num);
	}
	VectorMergeInsertSorter sorter(arr);
	sorter.vec_sort();

	std::cout << "Before: ";
	for (size_t i = 0; i < arr.size(); ++i)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "After:  ";
	sorter.vec_printArray();
	sorter.vec_printDuration();


	std::list<int> lst;
	for (int j = 1; j < ac; ++j)
	{
		std::istringstream iss2(av[j]);
		int num2;
		iss2 >> num2;
		if (iss2.fail() || !iss2.eof())
		{
			std::cout << RED << "Error: Invalid input '" << av[j] << "'. Please provide a valid integer." << END << std::endl;
			return 1;
		}
		if (num2 < 0)
		{
			std::cout << RED << "Error: Negative number '" << num2 << "' encountered. Please provide non-negative integers only." << END << std::endl;
			return 1;
		}
		lst.push_back(num2);
	}
	ListMergeInsertSorter sorter2(lst);
	
	sorter2.lst_sort();
	// 	std::cout << "Before: ";
	// for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
	// 	std::cout << *it << " ";
	// }
	// std::cout << std::endl;
	// std::cout << "After: ";
	// sorter2.lst_printList();
	sorter2.lst_printDuration();
	return 0;	
}

// std::vector:
// 内部的には動的配列として実装
// 要素は連続したメモリブロックに格納
// ランダムアクセスが可能
// 末尾への要素の追加や削除は高速ですが、先頭や中間への要素の追加や削除は遅い

// +---+---+---+---+---+
// | 0 | 1 | 2 | 3 | 4 |
// +---+---+---+---+---+


// std::deque (Double Ended Queue):
// 両端キュー
// 内部的には固定サイズの配列のリストとして実装
// ランダムアクセスが可能
// 要素は連続ではないメモリブロックに格納
// 先頭と末尾への要素の追加や削除は高速

// +---+---+       +---+---+       +---+---+
// | 0 | 1 |  ...  | 2 | 3 |  ...  | 4 | 5 |
// +---+---+       +---+---+       +---+---+


// std::list:

// 内部的には双方向連結リストとして実装
// 各要素はそれぞれ前と次の要素へのポインタを保持
// ランダムアクセスはサポートされていない。
// 要素にアクセスするには、リストを通じて反復する必要あり
// 先頭、中間、および末尾への要素の追加や削除は高速ですが、要素のアクセスは遅い

// ランダムアクセス
// std::vector<int> vec = {1, 2, 3, 4, 5};
// int value = vec[2];  // 3番目の要素に直接アクセス

// メモリ上でデータが連続していなければならない

// +---+    +---+    +---+
// | 0 | -> | 1 | -> | 2 |
// +---+    +---+    +---+

// 他にもシーケンスはあるがc＋９８はこれくらい

// vector と list の違い
// 1.データの格納:

// std::vector:
// データは連続したメモリブロックに格納されるため、
// キャッシュの効率が向上し、メモリアクセスが高速化される

// std::list:
// 各要素は個別のメモリブロックに格納され、
// 前後の要素へのポインタが含まれるので
// メモリアクセスが非連続であり、キャッシュの効率が低下する

// ２.要素へのアクセス:

// std::vector:
// 連続したメモリに格納されているため、
// インデックスを使って直接アクセスすることができ、アクセス速度が非常に高速
// std::list: 
// 要素へのアクセスはポインタをたどることによってのみ可能で、
// ランダムアクセスは非常に遅い


// 3.イテレータのインクリメントとデクリメント:

// std::vector:
// イテレータのインクリメントとデクリメントは非常に高速
// std::list:
// イテレータのインクリメントとデクリメントはポインタをたどる必要があるため、比較的遅い


// キャッシュ (Cache):
// CPUキャッシュは、頻繁にアクセスされるデータを高速に取得するために設計された小さくて高速なメモリで、
// 通常はCPUチップの内部に組み込まれている。キャッシュは主メモリ (RAM) からデータを事前に読み取り、CPUが必要とするデータをすばやく提供する

// データの局所性 (Locality):

// 空間局所性 (Spatial Locality):
// プログラムは、近くのメモリアドレスからデータを取得する傾向がある。つまり、一度にアクセスされるデータは、メモリ上で隣接している可能性が高い


// 時間局所性 (Temporal Locality): 
// プログラムは、短い時間の間に同じメモリアドレスに何度もアクセスする傾向がある、今回はそんなに関係ない

// キャッシュの効率に関わる要因:

// 連続したメモリアクセス:
// std::vectorはデータを連続したメモリブロックに格納するため、
// キャッシュの効率が高くなる。連続したメモリアクセスは、キャッシュライン（キャッシュの一部を占めるデータの塊）を効果的に使用し、
// メモリアクセスのオーバーヘッドを減らす。

// ランダムアクセス:
// std::listはデータを非連続的なメモリブロックに格納し、要素へのアクセスはポインタをたどることによって行われる
// これはキャッシュミス（CPUキャッシュに必要なデータがない状態）を引き起こしやすく、キャッシュの効率を低下させる

// キャッシュの効率が高いと、CPUはメモリアクセスのオーバーヘッドを減らし、プログラムの実行速度を向上させることができる