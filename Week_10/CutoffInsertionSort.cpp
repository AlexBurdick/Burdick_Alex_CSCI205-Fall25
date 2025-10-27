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
int CutoffInsertionSort::insertionSort(std::vector<int>& avector) {
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

// Overrides the regular sort to stop at the limit
int CutoffInsertionSort::sort(std::vector<int> &avector, int first, int last) {
	int splitpoint = 0;	// partition splitpoint index

	if (first<last) {									// if there is more than one element in the vector
		splitpoint = partition(avector, first, last);	// partition the vector from first to last
		//splitpoint = partition2(avector, first, last);
		sort(avector, first, splitpoint - 1);		// lower half
		sort(avector, splitpoint + 1, last);		// upper half
	}

	return swaps;
}