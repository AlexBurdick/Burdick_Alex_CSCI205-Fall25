#ifndef DUAL_SORT_H
#define DUAL_SORT_H

#include "QuickSortTest.h"

class DualPivotSort : public QuickSortTest {
private:
    const int LIMIT = 5;
    int partition(std::vector<int>&, int, int) override;
    void insertionSort(std::vector<int>&);

public:
    DualPivotSort()  { sortType = "Dual Pivot Sort"; }
    DualPivotSort(std::vector<std::pair<char, std::vector<int>>> v) : QuickSortTest{v}{}
    ~DualPivotSort(){}

    void sort(std::vector<int>&, int, int) override;
};

#endif