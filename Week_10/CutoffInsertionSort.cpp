#include "CutoffInsertionSort.h"

CutoffInsertionSort::CutoffInsertionSort(std::vector<int> &avector)
{
    setSortType("Cutoff_Insertion_Sort");
    setList(avector);
}

CutoffInsertionSort::~CutoffInsertionSort(){}

/*
Switch to insertion sort for arrays with size less than a pre-
decided limit. Once the size of the sub-array goes lower than the limit, apply insertion 
sort on that sub-array.
*/
int CutoffInsertionSort::insertionSort(std::vector<int> &avector)
{
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


/* Implements Lomuto partition scheme
selects the last element of the array as the pivot, iterates through the array, 
maintaining an index i that tracks the boundary between elements less than or equal 
to the pivot and those greater than the pivot. Elements less than or equal to the 
pivot are moved to the left side, and after the iteration, the pivot is placed in its 
correct final position by swapping it with the element at index i + 1. */
int CutoffInsertionSort::partition(std::vector<int> &avector, int low, int high)
{
    // choose the pivot
    int pivot = avector[high];
  
    // index of smaller element and indicates the right position of pivot found so far
    int i = low - 1;

    // Traverse arr[low..high] and move all smaller elements on left side. Elements 
    // from low to  i are smaller after every iteration
    for (int j = low; j <= high - 1; j++) {
        if (avector[j] < pivot) {
            i++;
            swap(avector[i], avector[j]);
            swaps++;
        }
    }

    // move pivot after smaller elements and return its position
    swap(avector[i + 1], avector[high]); 
    swaps++; 
    return i + 1;
}

// Overrides the regular sort to stop at the limit
int CutoffInsertionSort::sort(std::vector<int> &avector, int first, int last)
{
	int splitpoint = 0;

	if (first < last-limit) { // if there the vector is still above the limit size
		splitpoint = partition(avector, first, last);// partition the vector from first to last
		sort(avector, first, splitpoint - 1);	// lower half
		sort(avector, splitpoint + 1, last);	// upper half
	}

    swaps += insertionSort(avector);

	return swaps;
}