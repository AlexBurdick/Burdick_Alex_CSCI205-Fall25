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

#pragma region Function Prototypes
vector<int> generate_vector(int size, char type);
void print_vector(vector<int>& vec);

// Non-Comparison Sorts
int histogram(vector<int>&);
int prefixSum(vector<int>&);
int radixSort(vector<int>&);
#pragma endregion

/* 8.
Main should: Run each of the algorithms with various sizes of the array and different 
types of arrays (random, inverse, partial sort). Put graphs into .pdf and submit with 
lab. best way to compare a sort would be do a graph that show num of comparison, num 
of swaps, also look at selection sort. Measure number of moves needed to get something 
in place (aka swaps).
*/
int main() {
	const size_t SIZE = 50;
	vector<int> avector = generate_vector(SIZE, 'r');
	vector<int> gaps;
	const vector<string> SORTS = {	"BUBBLE_SORT",
									"COMB_SORT"
									"SELECTION_SORT",
									"INSERTION_SORT",
									"SHELL_SORT_N/2",
									"SHELL_SORT_KNUTH",
									"SHELL_SORT_HIBBARD",
									"SHELL_SORT_SEDGWICK",
							 	}; // "HISTOGRAM", "PREFIX_SUM", "RADIX_SORT"

	vector<SortAlgorithm> sorts =
	{
		{"Bubble Sort", bubbleSort},
		{"Insertion Sort", insertionSort}
		//{"Shell Sort", shellSort}
	};
/*
	vector<int> testVector = {45, 78, 23, 91, 12, 67, 45, 88, 34, 56, 78, 9, 67, 41, 
		23, 89, 56, 15, 72, 34, 91, 8, 45, 63, 29, 88, 51, 12, 74, 67, 38, 91, 56, 
		82, 23, 47, 91, 65, 12, 78, 34, 19, 88, 56, 73, 45, 27, 91, 62, 38};
	int counter = 0;
	for (size_t i = 0; i < SORTS.size(); i++)
	{
		string filename = "data/" + SORTS[i] + ".txt";
		cout << filename << endl;
		
		for (size_t j = 1; j < SIZE; j *= 10)
		{
			counter++;
			avector = generate_vector(SIZE, 'r');
			cout << counter << endl;
		}
		
	}
	
	

	cout << filename << endl;
	avector = generate_vector(SIZE, 'r');
	gaps = knuth_sequence(avector.size());
	cout << shellSort(avector, gaps) << endl;
*/
	cout << "SHELL SORT WITH HIBBARD GAP SEQUENCE" << endl;
	avector = generate_vector(SIZE, 'r');
	gaps = hibbard(avector.size());
	print_vector(avector);
	shellSort(avector, gaps);
	print_vector(avector);
	
	cout << "SHELL SORT WITH SEDGWICK GAP SEQUENCE" << endl;
	avector = generate_vector(SIZE, 'r');
	gaps = sedgwick(avector.size());
	print_vector(avector);
	shellSort(avector, gaps);
	print_vector(avector);

	//system("python grapher.py");

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
