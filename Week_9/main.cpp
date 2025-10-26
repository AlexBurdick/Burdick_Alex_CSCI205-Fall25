/*********************************************************************
 * @file  main.cpp
 * 
 * @brief Implementation of sort algorithm tests. The main program writes 
 * files to a folder called /data in the working directory. The graphing 
 * function creatings .png files to a folder called /graphs in the working 
 * directory.
 * Author: Alex Burdick
 * Date:   10/26/2025
 *********************************************************************/

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
void sort_test();

int main() {
	const int SIZE = 10000;

	// Vector of structs to create iterable functions
	vector<SortAlg> SORTS = {
		{"BUBBLE SORT", bubbleSort},
		{"COMB SORT", combSort},
		{"SELECTION SORT", selectionSort},
		{"INSERTION SORT", insertionSort},
		{"SHELL SORT N2", shellSort},
		{"SHELL SORT KNUTH", knuth_shellSort},
		{"SHELL_SORT HIBBARD", hibbard_shellSort},
		{"SHELL SORT SEDGWICK", sedgwick_shellSort},
		{"COUNTING SORT", countingSort},
		{"RADIX SORT", radixSort}
	};

	// Vector of testing vector types
	// 'a' = Ascending, 'd' = descending, 'r' = random, 'p' = partially sorted
	vector<char> vtypes = {'a', 'd', 'r', 'p'};

	for (char vtype : vtypes) {
		// Test for different array sizes
		for (auto& sort : SORTS) {
			string filename = "data/" + sort.name + "_" + vtype + ".txt";
			vector<vector<int>> results;

			for (int i = 10; i <= SIZE; i *= 2 ) {
				vector<int> avector = generate_vector(i, vtype);
				results.push_back( {i, sort.func(avector)} );
			}
			// Files will be writted to a direcotry called 'data' in the working direcotry
			sort.writeToFile(results, filename);
		}
	}

	// Launch graph, which will produce a different graph for each sort
	// The graphs will be stored in a directory called 'graphs' in the working directory
	system("python grapher.py");

	return 0;
}

// generates a random vector of size "size" with type "type"
// 'a' = ascending, 'd' = descending, 'r' = random, 'p' = partially sorted
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

// code to quickly see sort results
void sort_test() {
	vector<int> avector = {326, 4, 504, 82, 197};
	print_vector(avector);
	cout << radixSort(avector) << endl;
	print_vector(avector);
}