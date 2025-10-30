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

vector<int> mergeSort(vector<int> avector);
void merge(vector<int> &avector, vector<int> left, vector<int> right);
void printl(vector<int> avector);

int main(){
	int worst_case[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	int arr[] = {54, 26, 93, 17, 77, 31, 44, 55, 47, 5,};
	vector<int> avector(arr, arr + sizeof(arr) / sizeof(arr[0]));
	vector<int> vec = {
        42, 17, 89, 3, 56, 42, 91, 17, 24, 68,
        75, 3, 89, 50, 12, 42, 91, 63, 24, 75,
        8, 56, 12, 68, 31, 91, 42, 75, 24, 8,
        50, 17, 3, 63, 89, 56, 12, 42, 75, 24,
        91, 68, 31, 50, 8, 17, 42, 63, 89, 24,
        75, 56, 12, 3, 91, 68, 42, 50, 17, 31,
        8, 24, 75, 56, 63, 12, 89, 42, 91, 17,
        3, 50, 24, 68, 75, 8, 12, 31, 56, 42,
        89, 63, 17, 91, 24, 50, 75, 3, 12, 42,
        68, 8, 56, 31, 17, 89, 91, 24, 42, 75
    };

	const size_t SIZE = 100;

	// Create vector of sort tests
	vector<QuickSortTest*> tests {
		new LazyPivotSort(),
		new MedianOf3Sort(),
		new TukeysNintherSort(),
		new CutoffInsertionSort(),
		new DualPivotSort()
	};
	
	/*
	DualPivotSort t;
	printl(vec);
	t.sort(vec, 0, vec.size() - 1);
	printl(vec);
	cout << "Swaps = " << t.getSwaps();
	*/

	// Test all algorithms
	for (auto test : tests) {
		test->test(10, 10);  // Call test() on each algorithm
		cout << "---" << endl;
	}

    for (auto test : tests) delete test; // Clean up memory
	return 0;
}

// Utiltiy function for testing
void printl(vector<int> avector){
	cout << "--Vector--";
	for (unsigned i = 0; i < avector.size(); i++)
		cout << avector[i] << " ";
	cout << endl;
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

// function merges two sorted vector
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