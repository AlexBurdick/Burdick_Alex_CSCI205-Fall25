#include "medianOf3Sort.h"

MedianOf3Sort::MedianOf3Sort(std::vector<int> &avector)
{
    setSortType("Median_of_3_Sort");
    setList(avector);
}

MedianOf3Sort::~MedianOf3Sort(){}

// function returns the median of three values (left, center, right)
// Big O: time -> O(1), space -> O(1)
int MedianOf3Sort::medianOf3(std::vector<int> &v, int left, int right)
{
    int center = (left + right) / 2;	// find center
    swap(v[left], v[center]);			// get ready to sort the three
    if( v[left] > v[right] )			// look at left and right
        swap(v[left], v[right]);		// swap if necessary
    if(v[center] > v[right] )			// look at center and right
        swap(v[center], v[right]);		// swap if necessary
    swap(v[center], v[right]);			// put pivot on right
    return v[right];					// return pivot value
}

// function partitions vector around a pivot value
// Big O: time -> O(n) where n is the sub-vector size, space -> O(1)
int MedianOf3Sort::partition(std::vector<int> &avector, int low, int high)
{
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