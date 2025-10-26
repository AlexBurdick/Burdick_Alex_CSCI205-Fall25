/*********************************************************************
 * @file  main.cpp
 * 
 * @brief Implementation of the quick and merge sort tests.
 
 * g++ -g -Wall -pedantic -o a.out *.cpp *.hpp *.h
 * valgrind --tool=memcheck --leak-check=full ./a.out
 *********************************************************************/

#include <vector>
#include <iostream>
#include "quickSortTest.h"

using namespace std;

// Function prototypes
void printVector(vector<int> avector);

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

	printVector(avector);
	quickSort(avector, 0, avector.size() - 1);
	printVector(avector);

	return 0;
}

//utility function to print a vector
void printVector(vector<int> avector){
	for (unsigned i = 0; i < avector.size(); i++)
		cout << avector[i] << " ";
	cout << endl;
}