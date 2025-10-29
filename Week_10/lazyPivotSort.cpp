#include "LazyPivotSort.h"

LazyPivotSort::LazyPivotSort(std::vector<std::pair<char, std::vector<int>>> vec)
    : QuickSortTest{vec}
{
    sortType = "Lazy_Pivot_Sort";
}

LazyPivotSort::~LazyPivotSort(){}

/* Implements Lomuto partition scheme
selects the last element of the array as the pivot, iterates through the array, 
maintaining an index i that tracks the boundary between elements less than or equal 
to the pivot and those greater than the pivot. Elements less than or equal to the 
pivot are moved to the left side, and after the iteration, the pivot is placed in its 
correct final position by swapping it with the element at index i + 1. */
int LazyPivotSort::partition(std::vector<int> &avector, int low, int high)
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
        }
    }

    // move pivot after smaller elements and return its position
    swap(avector[i + 1], avector[high]); 
    return i + 1;
}