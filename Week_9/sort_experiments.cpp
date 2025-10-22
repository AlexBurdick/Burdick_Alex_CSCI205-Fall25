/************************************************************************************
 * Questions
 * - 2. What gaps are we supposed to use? The Marcin Ciura's gap sequence?
 * - for 9 it says it wanst:
 *      a. Gap Sorts: Comb with a shrink factor of 1.3 and Shell sort with the gap 
  		   sequences listed above.
  		b. Bubbly Sorts: Comb (1.3) and Regular Bubble
        This mentions comb sort twice, are we doing two different comparisons?

 * - What's the deal with these below?
 * Non-Comparison Sorts: The following sorting algorithms sort without comparing 
 * items. Implement the following algorithms, demonstrate that they work and plot 
 * their efficiency. 
 * In order to accomplish the ordering without comparisons, 
 * significant memory needs to be allocated. For each of the following sorts design 
 * experiments to graph their efficiency in terms of
 *  - Operations: array assignments will be of interest here
 * 	- Auxilliary memory: additional memory needs to be allocated
 * 	- Big O: Radix sorts operates in O(nk) time, where n is the number of keys, and 
 *    k is the key length(width). K = logbase(longest number). Count the relevant 
 *    operations and see if your algorithm conforms.
 * 
 * Histogram: see sheet
 * 
 * Prefix Sum: see sheet
 * 
 * Radix Sort: see sheet
 ***********************************************************************************/

#include <iostream>
#include "stdlib.h"
#include <vector>

// Function prototypes
std::vector<int> generate_vector(int size, char type);
void print_vector(std::vector<int>&);
void swap(std::vector<int>&, int, int);

// Sort algorithms
int combSort(std::vector<int>&); 
int shellSort(std::vector<int>&, std::vector<int>&);
std::vector<int> hibbard(int size);
std::vector<int> sedgwick(int size);
std::vector<int> knuth_sequence(int);

// Non-Comparison Sorts
void histogram(std::vector<int>&);
void prefixSum(std::vector<int>&);
void radixSort(std::vector<int>&);

// Basic Comparison Sorts
void bubbleSort(std::vector<int>& avector);

// ==================================================================================

/** 1. Comb Sort
 * @brief Applies the comb sort algorithm with a shrink factor of 1.3
 * 
 * @param vector<int>&
 * @return number of swaps
 */
int combSort(std::vector<int>& list)
{
    int gap     = list.size();
    int shrink  = 1.3;
    bool sorted = false;
    int swaps   = 0;

    // Loop
    while (sorted == false)
    {
        gap /= shrink; // Update the gap value for the next comb
        
        if (gap > 1) sorted = false; // Never sorted as long as gap > 1
        else         sorted = true; // If there are no swaps in this pass, we are done

        // A single 'comb' over the list
        for (int i = 0; i + gap < list.size(); i++)
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

/** 2. Shell Sort: Marcin Ciura ??
 * @brief Applies the shell sort algorithm to array using h values from the sequence 
 * array and returns the number of swaps or copies . . . however you want to view 
 * the inherent operation.
 * 
 * @param list 
 * @param sequence 
 * @return int 
 */
int shellSort(std::vector<int>& list, std::vector<int>& sequence)
{
    int swaps   = 0;

    return swaps;
}

/** 3. Shell Sort Gap: Hibbard Sequence
 * @brief Implements the Hibbard Sequence algorithm and returns an array of the 
 * sequence, based on size.
 * NOTE: I want you to write logic that creates the sequence . . . not simply copy it. 
 * You will need to create each sequence separately and then interleave them.
 * 
 * @param size 
 * @return std::vector<int> 
 */
std::vector<int> hibbard(int size)
{
    /*
    a. h = 1
    b. (2 ^ h) – 1
    c. h++
    */

    std::vector<int> sequence;
    
    return sequence;
}

/** 4. Shell Sort Gap: Sedgwick Sequence
 * @brief Implements the Sedgwick Sequence algorithm and returns a vector of the 
 * sequence based on size.
 * NOTE: I want you to write logic that creates the sequence . . . not simply copy it. 
 * You will need to create each sequence separately and then interleave them.
 * 
 * @param size 
 * @return std::vector<int> 
 */
std::vector<int> sedgwick(int size)
{
    /* Interleave the following two sets
    a. Set One (1, 19, 109, 505, 2161 . . .):
        i.   h = 0
        ii.  9(4 ^ h – 2 ^ h) + 1
        iii. h++
    b. Set Two (5, 41, 209, 929, 3905 . . .):
        i.   h = 0
        ii.  2 ^ (h + 2)(2 ^ (h + 2) – 3) + 1
        iii. h++
    */

    std::vector<int> sequence;
    
    return sequence;
}

/** 5. Shell Sort Gap: The Knuth Sequence
 * @brief You have been given this function in this weeks repo pull
 * NOTE: I want you to write logic that creates the sequence . . . not simply copy it.
 * 
 * @param size 
 * @return std::vector<int> 
 */
std::vector<int> knuth_sequence(int size){
    /*
    h = h * 3 + 1
    */

	std::vector<int> gap_sequence;
	int h = 1;
	while(h <= size / 3){ // 1/3 of the list size
		gap_sequence.push_back(h);
		h = h*3 + 1; 	// increase h
	}
	return gap_sequence;
}

// ==================================================================================
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
void bubbleSort(std::vector<int>& avector) { // O(n ^ 2)
	// iterate N, N-1, N-2, N-3 . . . etc times
	for (int pass = avector.size()-1; pass > 0; pass -= 1)
		for (int i = 0; i < pass; i++)
			if (avector[i] > avector[i+1])
				swap(avector, i, i+1);
	return;
}
// generates a random vector of size "size" with type "type"
// type = 'a' for ascending, 'd' for descending, 'r' for random, 'p' for partially sorted
std::vector<int> generate_vector(int size, char type){
	std::vector<int> temp(size);
	
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
				std::swap(temp[i], temp[i - 4]);
	}
	return temp;
}
// nicely formatted print function
void print_vector(std::vector<int>& vec){
	for (unsigned int i = 0; i < vec.size(); i++)
		std::cout<< vec[i] << " ";
	std::cout << std::endl;
}
// helper function to swap two vector elements
void swap(std::vector<int>& vec, int a, int b){
	int temp	= vec[a];
	vec[a]		= vec[b];
	vec[b]		= temp;
}