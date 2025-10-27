#ifndef MEDIAN_OF_3_SORT_H
#define MEDIAN_OF_3_SORT_H

#include "QuickSortTest.h"

class CutoffInsertionSort : public QuickSortTest {
private:
    // Limit varies from system to system and typically it is between 5 to 27
    const int limit = 5;

    int insertionSort(std::vector<int>&);

    // function partitions vector around a pivot value
    // Big O: time -> O(n) where n is the sub-vector size, space -> O(1)
    int partition(std::vector<int>&, int, int) override;

public:
    CutoffInsertionSort(std::vector<int>&);
    ~CutoffInsertionSort();

	int sort(std::vector<int>&, int, int);
};

#endif