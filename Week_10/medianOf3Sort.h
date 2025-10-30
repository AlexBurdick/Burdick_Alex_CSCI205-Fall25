#ifndef MEDIAN_OF_3_SORT_H
#define MEDIAN_OF_3_SORT_H

#include "QuickSortTest.h"

class MedianOf3Sort : public QuickSortTest {
private:
    // function partitions vector around a pivot value
    // Big O: time -> O(n) where n is the sub-vector size, space -> O(1)
    int partition(std::vector<int>&, int, int) override;

protected:
    // function returns the median of three values (left, center, right)
    // Big O: time -> O(1), space -> O(1)
    int medianOf3(std::vector<int>&, int, int);

public:
    MedianOf3Sort() = default;
    MedianOf3Sort(std::vector<std::pair<char, std::vector<int>>>);
    ~MedianOf3Sort();
};

#endif