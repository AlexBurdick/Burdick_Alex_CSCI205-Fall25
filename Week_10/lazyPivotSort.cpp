#include "lazyPivotSort.h"

LazyPivotSort::LazyPivotSort(std::vector<std::pair<char, std::vector<int>>> vec)
    : QuickSortTest{vec}
{
    sortType = "Lazy_Pivot_Sort";
}

LazyPivotSort::~LazyPivotSort(){}

// Hoare partition scheme
// Big O: time -> O(n) where n is the sub-vector size, space -> O(1)
int LazyPivotSort::partition(std::vector<int> &avector, int first, int last){
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