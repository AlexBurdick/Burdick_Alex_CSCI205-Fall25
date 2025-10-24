/************************************************************************************ 
 * Filename:	basic_comparison_sorts.cpp
 * Author:		Alex Burdick
 * Date:		10/26/2025
 * 
 * g++ -g -Wall -pedantic -o a.out *.cpp *.hpp *.h
 * valgrind --tool=memcheck --leak-check=full ./a.out
 ***********************************************************************************/

#include <iostream>
#include <fstream>
#include "stdlib.h"
#include <vector>
#include <cmath>
#include <filesystem>
#include "Sorts.hpp"

using namespace std;

vector<int> generate_vector(int size, char type);
void print_vector(vector<int>& vec);

/* 8.
Main should: Run each of the algorithms with various sizes of the array and different 
types of arrays (random, inverse, partial sort). Put graphs into .pdf and submit with 
lab. best way to compare a sort would be do a graph that show num of comparison, num 
of swaps, also look at selection sort. Measure number of moves needed to get something 
in place (aka swaps).
// Non-Comparison Sorts
int histogram(vector<int>&);
int prefixSum(vector<int>&);
int radixSort(vector<int>&);
*/
int main() {
	const size_t SIZE = 500;
	vector<SortAlgorithm> SORTS = {
		{"BUBBLE_SORT", bubbleSort},
		{"COMB_SORT", combSort},
		{"SELECTION_SORT", selectionSort},
		{"INSERTION_SORT", insertionSort},
		{"SHELL_SORT_N2", shellSort},
		{"SHELL_SORT_KNUTH", knuth_shellSort},
		{"SHELL_SORT_HIBBARD", hibbard_shellSort},
		{"SHELL_SORT_SEDGWICK", sedgwick_shellSort}

		// TO DO:
		// "HISTOGRAM", 
		// "PREFIX_SUM", 
		// "RADIX_SORT",
	};

	// Test for different array sizes
	for (auto& sort : SORTS) {
		string filename = "data/" + sort.name + ".txt";
		vector<vector<int>> results;

		for (int i = 10; i <= SIZE; i += 10 ) {
			vector<int> avector = generate_vector(i, 'r');
			results.push_back( {i, sort.func(avector)} );
		}

		sort.writeToFile(results, filename);
	}

	system("python grapher.py");

	return 0;
}

// generates a random vector of size "size" with type "type"
//  type = 'a' for ascending, 'd' for descending, 'r' for random, 'p' for partially sorted
vector<int> generate_vector(int size, char type){
	vector<int> temp(size);
	
	switch (type){
		case 'a': // ascending
			for(int i = 0; i < size; i++)
				temp[i] = i + 1;
			break;
		case 'd': // descending
			for(int i = 0; i < size; i++)
				temp[i] = size - i;
			break;
		case 'r': // random
			for(int i = 0; i < size; i++)
				temp[i] = rand() % 100;
			break;
		case 'p': // partially sorted
			for(int i = 0; i < size; i++)
				temp[i] = i + 1;
			// swap every 5th item
			for (size_t i = 4; i < temp.size(); i += 5) 
				swap(temp[i], temp[i - 4]);
	}
	return temp;
}

// nicely formatted print function
void print_vector(vector<int>& vec){
	for (unsigned int i = 0; i < vec.size(); i++)
		cout<< vec[i] << " ";
	cout << endl;
}
