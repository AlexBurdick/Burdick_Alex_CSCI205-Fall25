# ifndef SORTS_HPP
# define SORTS_HPP

#include <fstream>
#include <iostream>
#include "stdlib.h"
#include <vector>
#include <cmath>
#include <functional>

struct SortAlg {
    std::string name;
    std::function<int(std::vector<int>&)> func;
	
    // Write to file (from LeChat, 10/22/2025)
    void writeToFile(const std::vector<std::vector<int>>& data, const std::string& filename) {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return;
        }

        for (std::vector<int> nums : data)
            outFile << nums[0] << " " << nums[1] << std::endl;
        
        outFile.close();
    }
};

/**
 * @brief helper function to swap two vector elements
 * 
 * @param vec 
 * @param a 
 * @param b 
 */
void swap(std::vector<int>& vec, int a, int b){
    int temp	= vec[a];
    vec[a]		= vec[b];
    vec[b]		= temp;
}

/**
 * @brief modified insertion sort helper to work with gaps for the shell sort
 * 
 * @param avector 
 * @param start 
 * @param gap 
 * @return int 
 */
int gapInsertionSort(std::vector<int>& avector, int start, int gap) {
    int swaps = 0;
    for (size_t i = start + gap; i < avector.size(); i += gap) {
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

/**
 * @brief Bubble Sort
 * Memory	= O(1)
 * Time
 * ===============
 * Average	= O(N^2)
 * Best		= O(N) if optimized
 * Worst	= O(N^2)
 * 
 * @param avector
 * @return int
 */
int bubbleSort(std::vector<int>& avector) {
	int swaps = 0;
    // iterate N, N-1, N-2, N-3 . . . etc times
	for (int pass = static_cast<int>(avector.size()-1); pass > 0; pass -= 1)
		for (int i = 0; i < pass; i++)
			if (avector[i] > avector[i+1]){
                swap(avector, i, i+1);
                swaps++;
            }
	return swaps;
}

/**
 * @brief Comb sort algorithm with a shrink factor of 1.3
 * Memory	= O(1)
 * Time
 * ===============
 * Average	= O(N^2)
 * Best		= O(N) if optimized
 * Worst	= O(N^2)
 * 
 * @param avector
 * @return int
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

/**
 * @brief Selection sort
 * Memory	= O(1)
 * Time
 * ===============
 * Average	= O(N^2)
 * Best	= O(N^2)
 * Worst	= O(N^2)
 * 
 * @param avector 
 * @return int 
 */
int selectionSort(std::vector<int>& avector) {
	int swaps = 0;
    // iterate N, N-1, N-2, N-3 . . . etc times
	for (int fillslot = static_cast<int>(avector.size() - 1); fillslot >= 0; fillslot--) {
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

/**
 * @brief Insertion sort
 * Memory	= O(1)
 * Time
 * ===============
 * Average	= O(N^2)
 * Best		= O(N)
 * Worst	= O(N^2)
 * 
 * @param avector 
 * @return int 
 */
int insertionSort(std::vector<int>& avector) {
	int swaps = 0;
    for (size_t index =1; index < avector.size(); index++) {
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

/**
 * @brief Shell sort (N/2) using the gapInsertionSort helper
 * Memory	= O(1)
 * Time
 * ===============
 * Average	= O(N^2)
 * Best		= O(N)
 * Worst	= O(N^2)
 * 
 * @param avector 
 * @return int 
 */
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

#pragma region gap sequence Shell sorts
/**
 * @brief Shell sort to be used with the sequence functions, which act as helper functions
 * 
 * @param avector 
 * @param sequence 
 * @return int 
 */
int gap_shellSort(std::vector<int>& avector, std::vector<int>& sequence){
	int swaps = 0;
	// iterate through the gap sequence vector. Assumption is larger gaps at end of vector
	for(int i = sequence.size() - 1; i >= 0; --i){
		int gap = sequence[i]; // choose the current gap from the provided sequence

		// begin loop at "gap", look at all items that are "gap" idices apart
		for(int outer = gap; outer < static_cast<int>(avector.size()); outer++){
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

/**
 * @brief Shell sort (Knuth sequence)
 * Memory	= O(1)
 * Time
 * ===============
 * Average	= O(N^(3/2))
 * Best		= O(N*logN)
 * Worst	= O(N^2)
 * 
 * @param avector 
 * @return int 
 */
int knuth_shellSort(std::vector<int>& avector){
	std::vector<int> gap_sequence;
	int h = 1;
	while(h <= static_cast<int>(avector.size()) / 3) { // make sure that there will be a few comaprisons
		gap_sequence.push_back(h);
		h = h*3 + 1;
	}
	return gap_shellSort(avector, gap_sequence);
}

/**
 * @brief Shell sort (Hibbard sequence)
 * Memory	= O(1)
 * Time
 * ===============
 * Average	= O(N^(3/2))
 * Best		= O(N*logN)
 * Worst	= O(N^2)
 * 
 * @param avector 
 * @return int 
 */
int hibbard_shellSort(std::vector<int>& avector)
{
	std::vector<int> gap_sequence; // vector to hold sequence of ints
	int h = 1;
	int gap = pow(2, h) - 1;
	while( gap <= static_cast<int>(avector.size()) / 3 ){ // not greater than size
		gap_sequence.push_back(gap);
		h++;
		gap = pow(2, h) - 1;
	}
    
	return gap_shellSort(avector, gap_sequence);
}

/**
 * @brief Shell sort (Sedgwick sequence)
 * Memory	= O(1)
 * Time
 * ===============
 * Average	= O(N^(3/2))
 * Best		= O(N*logN)
 * Worst	= O(N^(4/3))
 * 
 * @param avector 
 * @return int 
 */
int sedgwick_shellSort(std::vector<int>& avector)
{
	// First sequence
    std::vector<int> seq1; // vector to hold sequence of ints
	int h = 0;
	int gap = 9 * ( pow(4, h) - pow(2, h) ) + 1;

	while( gap <= static_cast<int>(avector.size()) / 3 )
    {
		seq1.push_back(gap);
		h++;
		gap = 9 * ( pow(4, h) - pow(2, h) ) + 1;
	}
	
	// Second sequence
	std::vector<int> seq2; // vector to hold sequence of ints
	h = 0;
	gap = pow(2, h+2) * (pow(2, h+2) - 3) + 1;
	while( gap <= static_cast<int>(avector.size()) / 3 )
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
/**
 * @brief Prefix sum calculator to be used with counting sorts
 * 
 * @param histogram 
 */
void prefixSum(std::vector<int>& histogram) {
    for (size_t i = 1; i < histogram.size(); i++)
        histogram[i] += histogram[i-1];
}

/**
 * @brief Counting sort
 * Memory	= O(1)
 * Time
 * ===============
 * Average	= O(N)
 * Best		= O(N)
 * Worst	= O(N)
 * 
 * @param avector 
 * @return int 
 */
// Counting sort
int countingSort(std::vector<int>& avector) {
    if (avector.empty()) return 0; // Validation
	int swaps = 0;

    // Find the largest number in the array to be sorted
    int maxInt = avector[0]; // Assume first element is the max
    for (int num : avector)
        if (num > maxInt)  maxInt = num;

    // Place elements in histogram buckets
    std::vector<int> histogram(maxInt + 1, 0);
    for (int element : avector) {
        histogram[element]++;
        swaps++;
    }
    
    // Prefix sum
    prefixSum(histogram);

    // Temporary array to store sorted elements
    std::vector<int> sorted(avector.size());

    // Sort (needs to be int because of decrement)
    for (int i = static_cast<int>(avector.size()-1); i >= 0; i--) {
        sorted[histogram[avector[i]] - 1] = avector[i];
        histogram[avector[i]]--;
        swaps++;
    }

    // Reset old array to sorted array
    avector = sorted;
    return swaps;
}

/**
 * @brief Auxiliary function for radix sort (from Claude 10/24/2025)
 * 
 * @param arr 
 * @param exp 
 * @return int 
 */
int countSort(std::vector<int>& arr, int exp) {
    std::vector<int> output(arr.size());
    std::vector<int> count(10, 0); // Digits 0-9
	int swaps = 0;

    // Count occurrences of each digit
    for (int num : arr) {
        int digit = (num / exp) % 10;
        count[digit]++;
		swaps++;
    }

    // Compute prefix sum
    prefixSum(count);

    // Place elements in sorted order
    for (int i = static_cast<int>(arr.size()) - 1; i >= 0; --i) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
		swaps++;
    }

    // Copy the sorted elements back
    arr = output;
	return swaps;
}

/**
 * @brief Radix sort
 * Memory	= O(1)
 * Time
 * ===============
 * Average	= O(N)
 * Best		= O(N)
 * Worst	= O(N)
 * 
 * @param avector 
 * @return int 
 */
int radixSort(std::vector<int>& avector) {
    if (avector.empty()) return 0;
	int swaps = 0;

    // Find the largest number in the array to be sorted
    int maxInt = avector[0];
    for (int num : avector)
        if (num > maxInt)  maxInt = num;

    // Sort for every digit
    for (int exp = 1; maxInt / exp > 0; exp *= 10) {
        swaps += countSort(avector, exp);
    }

	return swaps;
}

#pragma endregion

# endif