#include "TukeysNintherSort.h"

TukeysNintherSort::TukeysNintherSort(std::vector<std::pair<char, std::vector<int>>> vec)
    : MedianOf3Sort{vec}
{
    sortType = "Tukeys_Ninther_Sort";
}

TukeysNintherSort::~TukeysNintherSort() {}

int TukeysNintherSort::ninther(std::vector<int>& vec, int left, int right)
{
    int pitvot = medianOf3(vec, left, right);
    return pitvot;
}

int TukeysNintherSort::partition(std::vector<int>& avector, int low, int high) {
    // pivot (Element to be placed at right position)
    int pivot = medianOf3(avector, low, high);	// better pivot choice
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
