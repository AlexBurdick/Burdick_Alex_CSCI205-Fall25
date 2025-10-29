#include "TukeysNintherSort.h"

TukeysNintherSort::TukeysNintherSort() { sortType = "Tukeys_Ninther_Sort"; }
TukeysNintherSort::~TukeysNintherSort() {}

int TukeysNintherSort::ninther(std::vector<int>& v, int left, int right) {
    return left;
}
/*
int TukeysNintherSort::partition(std::vector<int>& avector, int first, int last) {
    // Use Tukey's ninther for pivot selection
    int pivotIndex = ninther(avector, first, last);
    
    // Swap pivot to end position
    std::swap(avector[pivotIndex], avector[last]);
    
    // Then do standard partitioning (can call parent's partition logic)
    // ... your partitioning code
    
    return splitpoint;

    // pivot (Element to be placed at right position)
    int pivot = MedianOf3Sort::medianOf3(avector, low, high);	// better pivot choice
    int i = low - 1; 							// marker for the partition split point

    // traverse through all elements, compare each element with pivot
    // place smaller elements at the beginning of the partition (position i)
    for (int j = low; j <= high - 1; j++){
        if (avector[j] < pivot){				// If current element is smaller than the pivot
            i++; 								// increment index of smaller element
            swap(avector[i], avector[j]);		// swap items at i and j (j being smaller than pivot)
        }
    }

    swap(avector[i + 1], avector[high]);		// after partitioning, put pivot in it's place at splitpoint
    return i + 1;								// return the splitpoint
}
*/