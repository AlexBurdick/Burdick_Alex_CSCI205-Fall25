#include <iostream>
#include "stdlib.h"
#include <vector>

/* Questions:
- What reading is there for Database?
- 
*/

using namespace std;

vector<int> generate_vector(int size, char type);
void print_vector(vector<int>&);
void bubbleSort(vector<int>&);
void swap(vector<int>&, int, int);
void selectionSort(vector<int>&); 
void insertionSort(vector<int>&);

// Runestone Shell Sort
void gapInsertionSort(vector<int>&, int, int);
void shellSort(vector<int>&);

// Shell Sort that accepts a Gap Sequence
void shellSort(vector<int>&, vector<int>&);
vector<int> knuth_sequence(int);

int main() {

	const int SIZE = 50;

	cout << "BUBBLE SORT" << endl;
	vector<int> avector = generate_vector(SIZE, 'r');
	print_vector(avector);
	bubbleSort(avector);
	print_vector(avector);

	cout << endl;

	cout << "SELECTION SORT" << endl;
	avector = generate_vector(SIZE, 'r');
	print_vector(avector);
	selectionSort(avector);
	print_vector(avector);

	cout << endl;

	cout << "INSERTION SORT" << endl;
	avector = generate_vector(SIZE, 'r');
	print_vector(avector);
	insertionSort(avector);
	print_vector(avector);

	cout << endl;

	cout << "SHELL SORT WITH N/2 GAP SEQUENCE" << endl;
	avector = generate_vector(SIZE, 'r');
	print_vector(avector);
	shellSort(avector);
	print_vector(avector);

	cout << endl;
	
	cout << "SHELL SORT WITH KNUTH GAP SEQUENCE" << endl;
	avector = generate_vector(SIZE, 'r');
	vector<int> gaps = knuth_sequence(avector.size());
	print_vector(avector);
	shellSort(avector, gaps);
	print_vector(avector);

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

/*
	apply the bubble sort to a vector
	maintain invariant of all indices > passnum being sorted
	Compare a pair of adjacent items (a, b),
	Swap that pair if the items are out of order (in this case, when a > b),
	Repeat Step 1 and 2 until we reach the end of array
	(the last pair is the (N-2)-th and (N-1)-th items as we use 0-based indexing),
	By now, the largest item will be at the last position.
	We then reduce N by 1 and repeat Step 1 until we have N = 1.

	Memory	= O(1)
	
	Time
	===============
	Average	= O(N^2)
	Best	= O(N) if optimized
	Worst	= O(N^2)
*/
void bubbleSort(vector<int>& avector) { // O(n ^ 2)
	// iterate N, N-1, N-2, N-3 . . . etc times
	for (int pass = avector.size()-1; pass > 0; pass -= 1)
		for (int i = 0; i < pass; i++)
			if (avector[i] > avector[i+1])
				swap(avector, i, i+1);
	return;
}

/*
	apply the selection sort to a vector
	maintain invariant of all indices > fillslot being sorted
	Given an array of N items and L = 0, Selection Sort will:
	Find the position X of the largest (or smallest) item in the range of [L...N−1],
	This takes n-1 comparisons initially, then n-2, n-3 . . . etc
	Swap X-th item with the L-th item,
	Decrease the upper-bound L by 1 and repeat Step 1 until L = N-2.

	Memory	= O(1)

	Time
	===============
	Average	= O(N^2)
	Best	= O(N^2)
	Worst	= O(N^2)
*/
void selectionSort(vector<int>& avector) {
	// iterate N, N-1, N-2, N-3 . . . etc times
	for (int fillslot = avector.size() - 1; fillslot >= 0; fillslot--) {
		int positionOfMax = 0;
		for (int location = 1; location < fillslot + 1; location++){
			if (avector[location] > avector[positionOfMax])
				positionOfMax = location;
		}
		swap(avector, fillslot, positionOfMax);
	}
}

/*
	apply the insertion sort to a vector
	maintain invariant of all indices < position being sorted
	From each position, iterate towards 0, finding the insert point

	Memory	= O(1)
	
	Time
	===============
	Average	= O(N^2)
	Best	= O(N)
	Worst	= O(N^2)
*/
void insertionSort(vector<int>& avector) {
	for (unsigned int index =1; index<avector.size(); index++) {
		int current		 	= avector[index];			// remember current item
		unsigned int pos 	= index;					// need current position to move towards front
		while (pos>0 && avector[pos-1]>current) {		// while not at front and current item is less than previous
			avector[pos] = avector[pos-1];				// shift by 1 spot
			pos--; 										// keep moving towards front of vector
		}
		avector[pos] = current;							// place current item in opened spot
	}
}

// modified insertion sort helper to work with gaps for the shell sort
// same logic as the insertion but allows larger jumps
void gapInsertionSort(vector<int>& avector, int start, int gap) {
	for (unsigned int i = start + gap; i < avector.size(); i += gap) {
		int current		= avector[i];					// remember current item
		int pos			= i;							// need current position to move towards front
		while (pos >= gap && avector[pos - gap] > current) { // while not at front and current item is less than previous
			avector[pos] = avector[pos - gap];			// shift by "gap" spots
			pos		 	-= gap;							// decrease position by "gap"
		}
		avector[pos] = current;							// place current item in opened spot
	}
}

// function shellsorts through the vector, using the gapInsertionSort helper
void shellSort(vector<int>& avector) {
	int subvectorcount = avector.size() / 2; // first gap will be (size / 2)

	while (subvectorcount > 0) {
		for (int start = 0; start < subvectorcount; start++) 
			// apply gapped insertion sort with a gap of 'subvectorcount'
			gapInsertionSort(avector, start, subvectorcount);

		// just to see state of vector after each gap sort 
		cout << "After increments of size " << subvectorcount << " The vector is: " << endl;
		print_vector(avector);
		subvectorcount /= 2; // subsequent gaps (size/4), (size/8) . . . etc
	}
}

// apply the shell sort to a vector
// maintain invariant of all indices > passnum being sorted
void shellSort(vector<int>& avector, vector<int>& sequence){
	// iterate through the gap sequence vector. Assumption is larger gaps at end of vector
	for(int i = static_cast<int>(sequence.size()) - 1; i >= 0; --i){
		int gap = sequence[i]; // choose the current gap from the provided sequence

		// begin loop at "gap", look at all items that are "gap" idices apart
		for(int outer = gap; static_cast<int>(outer<avector.size()); outer++){
			int temp  = avector[outer]; // choose item at "gap" location
			int inner = outer;			// begin inner loop at "gap" location

			// apply the "gap sort" moving toward the front of the vector
			while(inner > gap-1 && avector[inner-gap] >= temp){
				avector[inner]	= avector[inner-gap];	// perform "gap level" shifts
				inner 			-= gap;					// decrease gap
			}
			avector[inner] = temp;						// place item in the sorted sub-vector
		 }
	}
}

// creates the Knuth sequence based on "size". Will stop at 1/3 of size
vector<int> knuth_sequence(int size){
	vector<int> gap_sequence;
	int h = 1;
	while(h <= size / 3){ // 1/3 of the list size
		gap_sequence.push_back(h);
		h = h*3 + 1; 	// increase h
	}
	return gap_sequence;
}

// generates a random vector of size "size" with type "type"
//  type = 'a' for ascending, 'd' for descending, 'r' for random, 'p' for partially sorted
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
