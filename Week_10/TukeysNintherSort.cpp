#include "TukeysNintherSort.h"

TukeysNintherSort::TukeysNintherSort(std::vector<std::pair<char, std::vector<int>>> vec)
    : QuickSortTest{vec}
{
    sortType = "Tukeys_Ninther_Sort";
}

TukeysNintherSort::~TukeysNintherSort() {}

int TukeysNintherSort::ninther(std::vector<int>& v, int left, int right)
{
    int depth = 0;
    const int MAX_DEPTH = 3;

    int center = (left + right) / 2;

    if (right - left < 3 || depth >= MAX_DEPTH)
    {
        if(  v[left] > v[center])   swap(v[left], v[center]);
        if(  v[left] > v[right])    swap(v[left], v[right]);
        if(v[center] > v[right])    swap(v[center], v[right]);
        swap(v[center], v[right]);
        return v[right];
    }
    
    int pivot1 = ninther(v, left, center);
    int pivot2 = ninther(v, center+1, right);

    return (pivot1 > pivot2) ? pivot1 : pivot2; 
}

// function partitions vector around a pivot value
// Big O: time -> O(n) where n is the sub-vector size, space -> O(1)
int TukeysNintherSort::partition(std::vector<int> &avector, int low, int high)
{
    // pivot (Element to be placed at right position)
    int pivot = ninther(avector, low, high);	// better pivot choice
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