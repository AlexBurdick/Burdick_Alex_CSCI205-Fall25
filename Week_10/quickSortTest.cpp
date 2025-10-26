#ifndef QUICK_SORT_TEST_CPP
#define QUICK_SORT_TEST_CPP

#include "quickSortTest.h"
#include <iostream>
#include <fstream>
#include <vector>

class quickSortTest {
private:
	std::string name;
	std::vector<int> list;

	// Write to file (from LeChat, 10/22/2025)
    void writeToFile(const std::vector<std::vector<int>>& data) {
        std::string filename = name + ".txt";
		std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return;
        }

        for (std::vector<int> nums : data)
            outFile << nums[0] << " " << nums[1] << std::endl;
        
        outFile.close();
    }

	// helper function to swap two vector elements
	void swap(int a, int b){
		int temp = a;
		a = b;
		b = temp;
	}

public:
	virtual ~quickSortTest() {}

	virtual void sort() {
        // Default implementation
        quickSort(list, 0, list.size() - 1);
    }

	virtual std::string getSortType() const {
        return "QuickSort";
    }
};

//recursive function that quicksorts a given vector
// Big O: time -> O(n log n) where n is the vector size, space -> O(1)
int quickSort(std::vector<int> &avector, int first, int last) {
	int swaps = 0;
	int splitpoint = 0;	// partition splitpoint index

	if (first<last) {									// if there is more than one element in the vector
		splitpoint = partition(avector, first, last);	// partition the vector from first to last
		//splitpoint = partition2(avector, first, last);
		quickSort(avector, first, splitpoint - 1);		// lower half
		quickSort(avector, splitpoint + 1, last);		// upper half
	}

	return swaps;
}

//function partitions vector around a pivot value
// returns the splitpoint index
// Big O: time -> O(n) where n is the sub-vector size, space -> O(1)
int partition(std::vector<int> &avector, int first, int last){
	int pivotValue = avector[last];	// grab the pivot (lazy approach: either first, last or middle element)
	//int pivotValue = medianOf3(avector, first, last);

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
		else swap(avector[rightmark], avector[leftmark]);	// pointers haven't crossed, perform a swap
	}
	
	// partition is done, put pivot in it's place. This will be it's final place in the sorted vector
	swap(avector[leftmark], avector[last]);	// place the pivot at splitpoint
	return leftmark;						// return split point
}

// function partitions vector around a pivot value
// Big O: time -> O(n) where n is the sub-vector size, space -> O(1)
int partition2(std::vector<int> &avector, int low, int high){
	// pivot (Element to be placed at right position)
	//int pivot = avector[high];				// grab the pivot (lazy approach: either first, last or middle element)

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

// function returns the median of three values (left, center, right)
// Big O: time -> O(1), space -> O(1)
int medianOf3(std::vector<int> &v, int left, int right){
	int center = (left + right) / 2;	// find center
	swap(v[left], v[center]);			// get ready to sort the three
	if( v[left] > v[right] )			// look at left and right
		swap(v[left], v[right]);		// swap if necessary
	if(v[center] > v[right] )			// look at center and right
		swap(v[center], v[right]);		// swap if necessary
	swap(v[center], v[right]);			// put pivot on right
	return v[right];					// return pivot value
}



#endif