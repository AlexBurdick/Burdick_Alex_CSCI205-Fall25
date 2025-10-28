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
#include "ListGenerator.hpp"

using namespace std;

// Function prototypes
void printVector(const std::vector<int>&);

/* TO DO:
1. Quicksort with lazy pivot choice of either right most or left most element
2. Quicksort with median of three pivot choice
3. Cutoff to insertion sort
4. Quicksort with Tukey’s ninther pivot choice
5. Dual pivot quicksort
*/
int main(){
	int worst_case[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	int arr[] = {54, 26, 93, 17, 77, 31, 44, 55, 47};
	//int arr[] = {6, 9, 4, 3, 10, 5, 7, 8, 1, 2};
	//vector<int> avector(worst_case, worst_case + sizeof(worst_case) / sizeof(worst_case[0]));
	vector<int> avector(arr, arr + sizeof(arr) / sizeof(arr[0]));

	// Assemble test vectors
	const size_t SIZE = 10;
	const vector<char> listTypes {'a', 'd', 'r', 'p'}; // Vector of list types
	vector<vector<int>> test_vectors;
	


	// Create vector of sort tests
	vector<QuickSortTest> tests {
		LazyPivotSort(avector),
		MedianOf3Sort(avector)
	};

	printVector(avector);
	tests[0].sort(avector, 0, avector.size() - 1);
	printVector(avector);

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