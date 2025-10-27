#ifndef MEDIAN_OF_3_SORT_H
#define MEDIAN_OF_3_SORT_H

#include "quickSortTest.h"

class medianOf3Sort : public quickSortTest {
private:
    // function returns the median of three values (left, center, right)
    // Big O: time -> O(1), space -> O(1)
    int medianOf3(std::vector<int>&, int, int);

    // function partitions vector around a pivot value
    // Big O: time -> O(n) where n is the sub-vector size, space -> O(1)
    int partition(std::vector<int>&, int, int) override;

public:
    medianOf3Sort(std::vector<int>&);
    ~medianOf3Sort();
};

#endif