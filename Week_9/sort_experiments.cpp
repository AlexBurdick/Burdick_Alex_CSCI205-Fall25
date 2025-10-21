/************************************************************************************
 * Questions
 * - 2. What gaps are we supposed to use? The Marcin Ciura's gap sequence?
 * 
 * 3. Shell Sort Gap: Hibbard Sequence: 
 * 		a. h = 1
 * 		b. (2 ^ h) – 1
 * 		c. h++
 * 		d. Write a function called vector<int> hibbard(int size) that implements the 
 * 		   Hibbard Sequence algorithm and returns an array of the sequence, based on 
 * 		   size.
 * 
 * 4. Shell Sort Gap: Sedgwick Sequence: Interleave the following two sets
 * 		a. Set One (1, 19, 109, 505, 2161 . . .):
 * 			i.   h = 0
 * 			ii.  9(4 ^ h – 2 ^ h) + 1
 * 			iii. h++
 * 		b. Set Two (5, 41, 209, 929, 3905 . . .):
 * 			i.   h = 0
 * 			ii.  2 ^ (h + 2)(2 ^ (h + 2) – 3) + 1
 * 			iii. h++
 * 		c. Write a function called vector<int> sedgwick(int size) that implements the 
 * 		   Sedgwick Sequence algorithm and returns a vector of the sequence based on 
 * 		   size.
 * 		   NOTE: I want you to write logic that creates the sequence . . . not simply 
 * 		   copy it. You will need to create each sequence separately and then 
 * 		   interleave them.
 * 
 * 5. Shell Sort Gap: The Knuth Sequence: h = h * 3 + 1
 * 		a. You have been given this function in this weeks repo pull
 * 		NOTE: I want you to write logic that creates the sequence . . . not simply copy it.
 * 
 * 9. Once you have gathered all data from your program plot the data using your 
 * 	  Python utility. Be sure that you have run the algorithms enough times to create 
 * 	  an informative graph depicting how each algorithm/gap sequence responds to the 
 * 	  varying input. You may want to create multiple graphs: One for size, one for 
 * 	  each type of array. Your graphs must be clearly labeled. Here are the graphs I 
 *    want to see
 * 		a. Gap Sorts: Comb with a shrink factor of 1.3 and Shell sort with the gap 
 * 		   sequences listed above.
 * 		b. Bubbly Sorts: Comb (1.3) and Regular Bubble
 * 
 * Non-Comparison Sorts: The following sorting algorithms sort without comparing 
 * items. Implement the following algorithms, demonstrate that they work and plot 
 * their efficiency. 
 * In order to accomplish the ordering without comparisons, 
 * significant memory needs to be allocated. For each of the following sorts design 
 * experiments to graph their efficiency in terms of
 * 		- Operations: array assignments will be of interest here
 * 		- Auxilliary memory: additional memory needs to be allocated
 * 		- Big O: Radix sorts operates in O(nk) time, where n is the number of keys, 
 * 		  and k is the key length(width). K = logbase(longest number). Count the 
 * 		  relevant operations and see if your algorithm conforms.
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
void swap(std::vector<int>&, int, int);

// Sort algorithms
int combSort(std::vector<int>&); 
int shellSort(std::vector<int>&, std::vector<int>&);
std::vector<int> hibbard(int size);
std::vector<int> sedgwick(int size);
std::vector<int> knuth_sequence(int);

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

// helper function to swap two vector elements
void swap(std::vector<int>& vec, int a, int b){
	int temp	= vec[a];
	vec[a]		= vec[b];
	vec[b]		= temp;
}



// ==================================================================================

/** 1.
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

/** 2.
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