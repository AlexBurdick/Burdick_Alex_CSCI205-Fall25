# ifndef SORTS_HPP
# define SORTS_HPP

#include <fstream>
#include "stdlib.h"
#include <vector>
#include <cmath>
#include <functional>

struct SortAlgorithm {
    std::string name;
    std::function<int(std::vector<int>&)> func;
    //std::function<void(std::vector<int>&, std::vector<int>&)> func;

    // Write to file (from LeChat, 10/22/2025)
    void writeToFile(const std::vector<std::vector<int>>& data, const std::string& filename) {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return;
        }

        for (std::vector<int> nums : data) {
            outFile << nums[0] << " " << nums[1] << std::endl;
        }
        outFile.close();
    }

};

// helper function to swap two vector elements
void swap(std::vector<int>& vec, int a, int b){
    int temp	= vec[a];
    vec[a]		= vec[b];
    vec[b]		= temp;
}

// modified insertion sort helper to work with gaps for the shell sort
int gapInsertionSort(std::vector<int>& avector, int start, int gap) {
    int swaps = 0;
    for (unsigned int i = start + gap; i < avector.size(); i += gap) {
        int current		= avector[i];					// remember current item
        int pos			= i;							// need current position to move towards front
        while (pos >= gap && avector[pos - gap] > current) { // while not at front and current item is less than previous
            avector[pos] = avector[pos - gap];			// shift by "gap" spots
            swaps++;
            pos		 	-= gap;							// decrease position by "gap"
        }
        avector[pos] = current;							// place current item in opened spot
    }
    return swaps;
}

#pragma region basic comparisons
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
int bubbleSort(std::vector<int>& avector) { // O(n ^ 2)
	int swaps = 0;
    // iterate N, N-1, N-2, N-3 . . . etc times
	for (int pass = avector.size()-1; pass > 0; pass -= 1)
		for (int i = 0; i < pass; i++)
			if (avector[i] > avector[i+1]){
                swap(avector, i, i+1);
                swaps++;
            }
	return swaps;
}

/** 1. Comb Sort
 * @brief Applies the comb sort algorithm with a shrink factor of 1.3
 * 
 * @param vector<int>&
 * @return number of swaps
 */
int combSort(std::vector<int>& list)
{
    int	   size 	= list.size();
	int    gap		= size;
    double shrink	= 1.3;
    bool   sorted	= false;
    int	   swaps	= 0;

    // Loop
    while (!sorted)
    {
        gap = static_cast<double>(gap) / shrink; // Update the gap value for the next comb
        
        if (gap > 1) sorted = false; // Never sorted as long as gap > 1
        else         sorted = true; // If there are no swaps in this pass, we are done

        // A single 'comb' over the list
        for (int i = 0; i + gap < size; i++)
        {
            if ( list[i] > list[i+gap] )
            {
                swap(list, i, i+gap);
                swaps++;
                sorted = false;
            }
        }
    }
    return swaps;
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
int selectionSort(std::vector<int>& avector) {
	int swaps = 0;
    // iterate N, N-1, N-2, N-3 . . . etc times
	for (int fillslot = avector.size() - 1; fillslot >= 0; fillslot--) {
		int positionOfMax = 0;
		for (int location = 1; location < fillslot + 1; location++){
			if (avector[location] > avector[positionOfMax])
				positionOfMax = location;
		}
		swap(avector, fillslot, positionOfMax);
        swaps++;
	}
    return swaps;
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
int insertionSort(std::vector<int>& avector) {
	int swaps = 0;
    for (unsigned int index =1; index<avector.size(); index++) {
		int current		 	= avector[index];			// remember current item
		unsigned int pos 	= index;					// need current position to move towards front
		while (pos>0 && avector[pos-1]>current) {		// while not at front and current item is less than previous
			avector[pos] = avector[pos-1];				// shift by 1 spot
            swaps++;
			pos--; 										// keep moving towards front of vector
		}
		avector[pos] = current;							// place current item in opened spot
	}
    return swaps;
}

// function shellsorts through the vector, using the gapInsertionSort helper
int shellSort(std::vector<int>& avector) {
	int subvectorcount = avector.size() / 2; // first gap will be (size / 2)
    int swaps = 0;

	while (subvectorcount > 0) {
		for (int start = 0; start < subvectorcount; start++) 
			// apply gapped insertion sort with a gap of 'subvectorcount'
			swaps = swaps + gapInsertionSort(avector, start, subvectorcount);

		// just to see state of vector after each gap sort 
		//std::cout << "After increments of size " << subvectorcount << " The vector is: " << std::endl;
		//print_vector(avector);
		subvectorcount /= 2; // subsequent gaps (size/4), (size/8) . . . etc
	}
    return swaps;
}
#pragma endregion

#pragma region Shell sorts
// apply the shell sort to a vector
// maintain invariant of all indices > passnum being sorted
int gap_shellSort(std::vector<int>& avector, std::vector<int>& sequence){
	int swaps = 0;
	// iterate through the gap sequence vector. Assumption is larger gaps at end of vector
	for(int i = static_cast<int>(sequence.size()) - 1; i >= 0; --i){
		int gap = sequence[i]; // choose the current gap from the provided sequence

		// begin loop at "gap", look at all items that are "gap" idices apart
		for(int outer = gap; static_cast<int>(outer < avector.size()); outer++){
			int temp  = avector[outer]; // choose item at "gap" location
			int inner = outer;			// begin inner loop at "gap" location

			// apply the "gap sort" moving toward the front of the vector
			while(inner > gap-1 && avector[inner-gap] > temp){
				avector[inner] = avector[inner-gap]; // perform "gap level" shifts
				swaps ++;
				inner -= gap; // decrease gap
			}
			avector[inner] = temp; // place item in the sorted sub-vector
		 }
	}
	return swaps;
}

// creates the Knuth sequence based on "size". Will stop at 1/3 of size
int knuth_shellSort(std::vector<int>& avector){
	std::vector<int> gap_sequence;
	int h = 1;
	while(h <= avector.size() / 3) { // make sure that there will be a few comaprisons
		gap_sequence.push_back(h);
		h = h*3 + 1;
	}
	return gap_shellSort(avector, gap_sequence);
}

/** 3. Shell Sort Gap: Hibbard Sequence
 * @brief Implements the Hibbard Sequence algorithm and returns an array of the 
 * sequence, based on size.
 * NOTE: I want you to write logic that creates the sequence . . . not simply copy it. 
 * You will need to create each sequence separately and then interleave them.
 * 
 * @param vector<int>& 
 * @return int number of swaps made
 */
int hibbard_shellSort(std::vector<int>& avector)
{
	std::vector<int> gap_sequence; // vector to hold sequence of ints
	int h = 1;
	int gap = pow(2, h) - 1;
	while( gap <= avector.size() / 3 ){ // not greater than size
		gap_sequence.push_back(gap);
		h++;
		gap = pow(2, h) - 1;
	}
    
	return gap_shellSort(avector, gap_sequence);
}

/** 4. Shell Sort Gap: Sedgwick Sequence
 * @brief Implements the Sedgwick Sequence algorithm and returns a vector of the 
 * sequence based on size.
 * NOTE: I want you to write logic that creates the sequence . . . not simply copy it. 
 * You will need to create each sequence separately and then interleave them.
 * 
 * @param vector<int>& 
 * @return int number of swaps made
 */
int sedgwick_shellSort(std::vector<int>& avector)
{
	// First sequence
    std::vector<int> seq1; // vector to hold sequence of ints
	int h = 0;
	int gap = 9 * ( pow(4, h) - pow(2, h) ) + 1;

	while( gap <= avector.size() / 3 )
    {
		seq1.push_back(gap);
		h++;
		gap = 9 * ( pow(4, h) - pow(2, h) ) + 1;
	}
	
	// Second sequence
	std::vector<int> seq2; // vector to hold sequence of ints
	h = 0;
	gap = pow(2, h+2) * (pow(2, h+2) - 3) + 1;
	while( gap <= avector.size() / 3 )
    {
		seq2.push_back(gap);
		h++;
		gap = pow(2, h+2) * (pow(2, h+2) - 3) + 1;
	}

	// Combinded sequence
    std::vector<int> gap_sequence;
	size_t maxSize = std::max(seq1.size(), seq2.size());
	for (size_t i = 0; i < maxSize; i++)
    {
		if (i < seq1.size())  gap_sequence.push_back(seq1[i]);
        if (i < seq2.size())  gap_sequence.push_back(seq2[i]);
	}

    return gap_shellSort(avector, gap_sequence);
}
#pragma endregion

#pragma region Counting sorts
// Prefix-sum
void prefixSum(std::vector<int>& avector) {
    for (size_t i = 0; i < avector.size()-1; i++)
        avector[i+1] += avector[i];
}

// Counting sort
int countingSort(std::vector<int>& avector) {
    int swaps = 0;

    // Find the largest number in the array to be sorted
    int maxInt = avector[0]; // Assume first element is the max
    for (int num : avector)
        if (num > maxInt)  maxInt = num;

    // Place elements in histogram buckets
    std::vector<int> histogram(maxInt + 1);
    for (int element : avector) {
        histogram[element]++;
        swaps++;
    }
    
    // Prefix sum
    prefixSum(avector);

    // Temporary array to store sorted elements
    std::vector<int> sortedArr(avector.size());

    // Sort
    for (size_t i = avector.size()-1; i = 0; i--) {
        sortedArr[histogram[avector[i]]] = avector[i];
        histogram[avector[i]]--;
        swaps++;
    }

    // Reset old array to sorted array
    avector = sortedArr;
    return swaps;
}

// Radix sort

#pragma endregion

# endif