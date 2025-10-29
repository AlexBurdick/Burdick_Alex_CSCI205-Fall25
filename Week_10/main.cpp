/*********************************************************************
 * @file  main.cpp
 * 
 * @brief Implementation of the quick and merge sort tests.
 
 * g++ -g -Wall -pedantic -o a.out *.cpp *.hpp *.h
 * valgrind --tool=memcheck --leak-check=full ./a.out
 *********************************************************************/

#include <vector>
#include <iostream>
#include "QuickSortTest.h"
#include "LazyPivotSort.h"
#include "MedianOf3Sort.h"
#include "CutoffInsertionSort.h"
#include "DualPivotSort.h"
#include "TukeysNintherSort.h"
#include "ListGenerator.hpp"

using namespace std;

int main(){
	const size_t SIZE = 100;
	
	// Create test lists
	ListGenerator lg = ListGenerator(SIZE);
	vector<pair<char, vector<int>>> testLists = lg.getLists();

	lg.printAllLists();

	// Create vector of sort tests
	vector<QuickSortTest*> tests {
		new LazyPivotSort(testLists),
		new MedianOf3Sort(testLists),
		new TukeysNintherSort(testLists),
		new CutoffInsertionSort(testLists),
		new DualPivotSort(testLists)
	};

	// Test all algorithms
	for (auto test : tests) {
		test->test();  // Call test() on each algorithm
		cout << "---" << endl;
	}

    for (auto test : tests) delete test; // Clean up memory
	return 0;
}