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

using namespace std;

// Function prototypes
void printVector(const std::vector<int>&);

int main(){
	int worst_case[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	int arr[] = {54, 26, 93, 17, 77, 31, 44, 55, 47};
	//int arr[] = {6, 9, 4, 3, 10, 5, 7, 8, 1, 2};
	//vector<int> avector(worst_case, worst_case + sizeof(worst_case) / sizeof(worst_case[0]));
	vector<int> avector(arr, arr + sizeof(arr) / sizeof(arr[0]));
	
	// Create vector of sort tests
	vector<QuickSortTest*> tests {
		new LazyPivotSort(),
		new MedianOf3Sort(),
		new TukeysNintherSort(),
		new CutoffInsertionSort(),
		new DualPivotSort()
	};



    for (auto test : tests) delete test; // Clean up memory
	return 0;
}

/**
 * @brief Utility function to print a vector
 * 
 * @param avector 
 */
void printVector(const std::vector<int>& avector){
	for (unsigned i = 0; i < avector.size(); i++)
		std::cout << avector[i] << " ";
	std::cout << std::endl;
}