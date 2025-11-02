#include "MergeSort.h"

// Dummy override
int MergeSort::partition(std::vector<int> &avector, int low, int high){return 0;}

// function sorts using mergesort.
// Big O: time -> O(n log n) where n is the vector size, space -> O(n)
// Note: this implementation uses auxiliary memory
// Each recursive call creates two new vectors of size n/2
vector<int> MergeSort::mergeSort(vector<int> avector)
{
	recursionDepth++;  // Increment current depth
	maxRecursions = max(maxRecursions, recursionDepth);  // Update max depth

	if (avector.size() <= insertionLIMIT)
	{
        insertionSort(avector);  // Sort the small array directly
        recursionDepth--;
		return avector;
    }

	int size = avector.size();				// get vector size
	if (size>1) {							// base case, range of 1 is sorted
		int mid = size/2;					// calculate mid point

		// split vector at midpoint: auxiliary memory created. These are new vectors
		vector<int> lefthalf(avector.begin(),avector.begin()+mid);
		vector<int> righthalf(avector.begin()+mid,avector.begin()+size);

		// merge sort the halves
		lefthalf  = mergeSort(lefthalf);	// recursive call to mergeSort the left half
		righthalf = mergeSort(righthalf);	// recursive call to mergeSort the right half
		
		// merge sorted sub vectors back into original vector
		merge(avector, lefthalf, righthalf);
	}
	recursionDepth--;  // Decrement current depth as recursion unwinds
	return avector;
}

// function merges two sorted vector
// Big O: time -> O(n) where n is the sub-vector size, space -> O(1)
void MergeSort::merge(vector<int> &avector, vector<int> left, vector<int> right){
	unsigned i = 0;	// left vector index
	unsigned j = 0;	// right vector index
	unsigned k = 0;	// merged vector index

	// while there are elements in both sub vectors
	while (i < left.size() && j < right.size()){
		if (left[i] < right[j])
			avector[k] = left[i++];		// copy from left
		else avector[k] = right[j++];	// copy from right
		k++;
	}
	// one of the vectors is exhausted. Can unconditionally copy from here
	while (i < left.size())
		avector[k++] = left[i++];		// copy from left

	while (j < right.size())
		avector[k++] = right[j++];		// copy from right
}

// Overrides the regular sort to stop at the limit
void MergeSort::sort(std::vector<int> &avector, int first, int last)
{
	mergeSort(avector);
}