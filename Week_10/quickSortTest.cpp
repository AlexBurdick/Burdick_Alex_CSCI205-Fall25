#ifndef QUICK_SORT_TEST_H
#define QUICK_SORT_TEST_H

#include "quickSortTest.h"
#include <vector>

// Constructor implementations
quickSortTest::quickSortTest() = default;
quickSortTest::quickSortTest(std::vector<int> &avector) : list(avector) {}

// Destructor
quickSortTest::~quickSortTest() {}

//recursive function that quicksorts a given vector
// Big O: time -> O(n log n) where n is the vector size, space -> O(1)
int quickSortTest::sort(std::vector<int> &avector, int first, int last) {
	int splitpoint = 0;	// partition splitpoint index

	if (first<last) {									// if there is more than one element in the vector
		splitpoint = partition(avector, first, last);	// partition the vector from first to last
		//splitpoint = partition2(avector, first, last);
		sort(avector, first, splitpoint - 1);		// lower half
		sort(avector, splitpoint + 1, last);		// upper half
	}

	return swaps;
}

std::string quickSortTest::getSortType() const {
    return sortType;
}

#endif