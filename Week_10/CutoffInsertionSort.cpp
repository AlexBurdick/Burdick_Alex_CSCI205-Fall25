#include "CutoffInsertionSort.h"

/*
Switch to insertion sort for arrays with size less than a pre-decided limit. Once the 
size of the sub-array goes lower than the limit, apply insertion sort on that sub-array.
*/
void CutoffInsertionSort::insertionSort(std::vector<int> &avector){
    for (unsigned int index = 1; index<avector.size(); index++) {
        int current		 = avector[index];			// remember current item
        unsigned int pos = index;					// need current position to move towards front
        while (pos>0 && avector[pos-1]>current) {	// while not at front and current item is less than previous
            swap(avector[pos], avector[pos-1]);		// shift by 1 spot
            pos--; 									// keep moving towards front of vector
        }
        avector[pos] = current;						// place current item in opened spot
    }
}

// Hoare partition scheme
// Big O: time -> O(n) where n is the sub-vector size, space -> O(1)
int CutoffInsertionSort::partition(std::vector<int> &avector, int first, int last){
    int pivotValue = avector[last];	// grab the pivot (lazy approach: either first, last or middle element)

    int rightmark  = last - 1;		// establish right pointer
    int leftmark   = first;			// establish left pointer

    bool done = false;				// flag to indicate when done

    while (!done){					// while not done
        // increment left pointer until a value larger than the pivot is found
        // while pointers haven't crossed and value at left pointer is less than or equal to pivot
        while (leftmark <= rightmark && avector[leftmark] <= pivotValue)
            leftmark++;

        // decrement right pointer until a value smaller than the pivot is found
        // while pointers haven't crossed and value at right pointer is greater than or equal to pivot
        while (rightmark >= leftmark && avector[rightmark] >= pivotValue)
            rightmark--;
        
        if (rightmark < leftmark) done = true;				// if pointers cross, the partition is done
        else{
            swap(avector[rightmark], avector[leftmark]);	// pointers haven't crossed, perform a swap
            swaps++;
        }
    }
    
    // partition is done, put pivot in it's place. This will be it's final place in the sorted vector
    swap(avector[leftmark], avector[last]);	// place the pivot at splitpoint
    swaps++;
    return leftmark;						// return split point
}

// Overrides the regular sort to stop at the limit
void CutoffInsertionSort::sort(std::vector<int> &avector, int first, int last)
{
	int splitpoint = 0;

	if( first < (last - limit) )
        insertionSort(avector);
    else
    {
		splitpoint = partition(avector, first, last);// partition the vector from first to last
		sort(avector, first, splitpoint - 1);	// lower half
		sort(avector, splitpoint + 1, last);	// upper half
	}
}