/*
Invariant = concept within the data organization that is not going to vary no matter what
(a list of 1 is already sorted, base case for recursion)
Stable = duplicate items maintain their relative position

Bubble Sorts
- will have two nested for loops, ineffiecient because of cost of swap
- very inefficient because they are very swap heavy
- improve efficiency by counting the number of swaps needed at each pass
- Stable
- Time efficiency in any case (best, worst, ave) is O(n²) (unless improved)
- Spacial efficiency O(1) (aka sorting things in place)
- Best case is already sorted, Worst case is sorted the wrong way
- Invariant: After one run, the last item is in place. After n iterations, it has n sorted items

Binary Sort
- requires randomly accessible memory, so arrays are good linked lists are not

Selection sort: constant in time, quadratic in space
- minimizes number of swaps (preferable to bubble sort)
- two nested loops
- step 1, iterate through collection and mark the smallest one, then put it at front (1 swap)
- Invariant: smallest is at front after first step
- step 2, do the same again - find smallest in collection (no need to look at first)
- Time efficiency O(n²)
- Spacial efficiency O(1)

Insertion Sort
- inserts new item into a sorted list, in a sort it marks the first element in the list as first of a new logical list and considers it already sorted
- assumes the first element is already sorted (not necessarily in its final place)
- new (or next) elemente gets compared until it finds its place, then gets inserted
- two nested loops (for, while) going the oppiste direction, one increases the other decreases
    - first is in order, looks at next, compared to already sorted part, places in order
    - looks at next, if smaller than second, second gets moved and third gets inserted
- Stable
- Invariant: first position is already sorted (or any item in the sorted part of the list)
- Best case, already sorted (no shifts, inner loop never runs) O(n)
- Average case, ranfomly sorted O(n²)
- Worst case, inversly sorted O(n²)
- Time efficiency O(n²)
- Spacial efficiency O(1)

Shell Sort
- optimized insertion sort
*/

/* g++ -g -Wall -pedantic -o a.out *.cpp *.hpp *.h
 * valgrind --tool=memcheck --leak-check=full ./a.out
 */
#include <iostream>
#include "stdlib.h"
#include <vector>

using namespace std;

// Lab i- design experiments for sorting algorithms

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