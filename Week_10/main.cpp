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

//utility function to print a vector
void printl(vector<int> avector){
	for (unsigned i = 0; i < avector.size(); i++)
		cout << avector[i] << " ";
	cout << endl;
}

int main(){
	int worst_case[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	int arr[] = {54, 26, 93, 17, 77, 31, 44, 55, 47};
	vector<int> avector(arr, arr + sizeof(arr) / sizeof(arr[0]));

	const size_t SIZE = 100;
	// Create test lists
	ListGenerator lg(SIZE);
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

	
	TukeysNintherSort ttrryy();


	// Test all algorithms
	for (auto test : tests) {
		test->test();  // Call test() on each algorithm
		cout << "---" << endl;
	}

    for (auto test : tests) delete test; // Clean up memory
	return 0;
}

// function sorts using mergesort.
// Big O: time -> O(n log n) where n is the vector size, space -> O(n)
// Note: this implementation uses auxiliary memory
// Each recursive call creates two new vectors of size n/2
vector<int> mergeSort(vector<int> avector) {
	int size = avector.size();				// get vector size
	if (size>1) {							// base case, range of 1 is sorted
		int mid = size/2;					// calculate mid point

		// split vector at midpoint: auxiliary memory created. These are new vectors
		vector<int> lefthalf(avector.begin(),avector.begin()+mid);
		vector<int> righthalf(avector.begin()+mid,avector.begin()+size);

		// merge sort the halves
		lefthalf  = mergeSort(lefthalf);	// recursive call to mergeSort the left half
		righthalf = mergeSort(righthalf);	// recursive call to mergeSort the right half
		
		// merge sorted sub vectors back into original vector
		merge(avector, lefthalf, righthalf);
	}
	return avector;
}

// function merges two sorted vectors
// Big O: time -> O(n) where n is the sub-vector size, space -> O(1)
void merge(vector<int> &avector, vector<int> left, vector<int> right){
	unsigned i = 0;	// left vector index
	unsigned j = 0;	// right vector index
	unsigned k = 0;	// merged vector index

	// while there are elements in both sub vectors
	while (i < left.size() && j < right.size()){
		if (left[i] < right[j])
			avector[k] = left[i++];		// copy from left
		else avector[k] = right[j++];	// copy from right
		k++;
	}
	// one of the vectors is exhausted. Can unconditionally copy from here
	while (i < left.size())
		avector[k++] = left[i++];		// copy from left

	while (j < right.size())
		avector[k++] = right[j++];		// copy from right
}