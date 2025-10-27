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

using namespace std;

// Function prototypes
void printVector(vector<int> avector);
vector<int> generate_vector(int size, char type);

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

	// Create vector of sort tests
    vector<QuickSortTest> tests {
		LazyPivotSort(avector),
		MedianOf3Sort(avector)
	};

	LazyPivotSort sorttest = LazyPivotSort(avector);

	printVector(avector);
	tests[0].sort(avector, 0, avector.size() - 1);
	printVector(avector);

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

//utility function to print a vector
void printVector(vector<int> avector){
	for (unsigned i = 0; i < avector.size(); i++)
		cout << avector[i] << " ";
	cout << endl;
}