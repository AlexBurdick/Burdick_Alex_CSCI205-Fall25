/*
Bubble Sorts
- will have two nested for loops, ineffiecient because of cost of swap
- very inefficient because they are very swap heavy
- improve efficiency by counting the number of swaps needed at each pass
- Bubble sort is secure, this means duplicate items maintain their relative position
- Time efficiency in any case (best, worst, ave) is O(n²) (unless improved)
- Spacial efficiency O(1) (aka sorting things in place)
- Best case is already sorted, Worst case is sorted the wrong way
- Invariant: After one run, the last item is in place. After n iterations, it has n sorted items

Invariant: concept within the data organization that is not going to vary no matter what

Binary Sort
- requires randomly accessible memory, so arrays are good linked lists are not

Selection sort: constant in time, quadratic in space
- minimizes number of swaps (preferable to bubble sort)
- two nested loops
- step 1, iterate through collection and mark the smallest one, then put it at front (1 swap)
- Invariant: smallest is at front after first step
- step 2, do the same again - find smallest in collection (no need to look at first)
- 
*/ 

#include <iostream>
#include "stdlib.h"
#include <vector>

using namespace std;

// Function prototypes
void print_vector(vector<int>&);
void swap(vector<int>&, int, int);

int main() {
    return 0;
}

// nicely formatted print function
void print_vector(vector<int>& vec){
	for (unsigned int i = 0; i < vec.size(); i++)
		cout<< vec[i] << " ";
	cout << endl;
}

// helper function to swap two vector elements
void swap(vector<int>& vec, int a, int b){
	int temp	= vec[a];
	vec[a]		= vec[b];
	vec[b]		= temp;
}