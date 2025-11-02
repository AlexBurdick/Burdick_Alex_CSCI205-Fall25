/*********************************************************************
 * @file  main.cpp
 * 
 * @brief Implementation of the quick and merge sort tests.
 
 * g++ -g -Wall -pedantic -o a.out *.cpp *.hpp *.h
 * valgrind --tool=memcheck --leak-check=full ./a.out
 *********************************************************************/

#include <vector>
#include <iostream>
#include <algorithm>
#include "QuickSortTest.h"
#include "LazyPivotSort.h"
#include "MedianOf3Sort.h"
#include "CutoffInsertionSort.h"
#include "DualPivotSort.h"
#include "TukeysNintherSort.h"
#include "ListGenerator.hpp"
#include "MergeSort.h"

using namespace std;

// Global variables
const size_t SIZE = 1000;
const size_t INCR = 100;

int main(){
/*
	// QUICK SORT TESTING
	vector<QuickSortTest*> tests1{ // Create vector of sort tests
		new LazyPivotSort(),
		new MedianOf3Sort(),
		new TukeysNintherSort(),
		new CutoffInsertionSort(),
		new DualPivotSort()
	};
	for (auto test : tests1){ // Test all sorting algorithms
		test->test(SIZE, INCR);  // Call test on each algorithm
		cout << "---" << endl;
	}
	for (auto test : tests1) delete test; // Clean up memory

	// WORST CASE TESTING
	vector<QuickSortTest*> tests2{ // Create vector of sort tests
		new LazyPivotSort(),
		new MedianOf3Sort(),
		new TukeysNintherSort()
	};

	for(size_t i = 0; i <= SIZE; i += INCR)
	{
		for(auto test : tests2)
		{
			test->resetCounters();

			vector<int> v = ListGenerator::generateList(i, 'd');
			test->sort(v, 0, v.size()-1);  // Call test on each algorithm
			
			cout << test->getSortType() << endl;
			cout << "Comparisons: " << test->getComparisons() << endl;
			cout << "Swaps: " << test->getSwaps() << endl;
			cout << "---" << endl;
			
			test->appendTestResults(i, test->getComparisons());
		}
	}

	for(auto test : tests2)
	{
		string filename = "experiment2_3/" + test->getSortType() + ".txt";
		ofstream outFile(filename);
		if (!outFile.is_open())
		{
			cerr << "Error: Could not open file " << filename << std::endl;
			continue;
		}

		std::vector<std::pair<int, int>> testResults = test->getTestResults();
		for(auto r : testResults)
			outFile << r.first << " " << r.second << std::endl;
		outFile.close();
	}
	// Clean up memory
	for(auto test : tests2) delete test;
*/
	// RECURSION SORT TESTING
	vector<QuickSortTest*> tests3{ // Create vector of sort tests
		new DualPivotSort(),
		new MedianOf3Sort(),
		new TukeysNintherSort(),
		new MergeSort()	
	};

	for(size_t i = 0; i <= SIZE; i += INCR)
	{
		for(auto test : tests3)
		{
			test->resetCounters();

			vector<int> v = ListGenerator::generateList(i, 'r');
			test->sort(v, 0, v.size()-1);  // Call test on each algorithm

			cout << test->getSortType() << endl;
			cout << "Recursions: " << test->getRecursions() << endl;
			cout << "---" << endl;

			test->appendTestResults(i, test->getRecursions());
		}
	}

	for(auto test : tests3)
	{
		string filename = "experiment3/" + test->getSortType() + ".txt";
		ofstream outFile(filename);
		if (!outFile.is_open())
		{
			cerr << "Error: Could not open file " << filename << std::endl;
			continue;
		}

		std::vector<std::pair<int, int>> testResults = test->getTestResults();
		for(auto r : testResults)
			outFile << r.first << " " << r.second << std::endl;
		outFile.close();
	}
	// Clean up memory
	for(auto test : tests3) delete test;
}