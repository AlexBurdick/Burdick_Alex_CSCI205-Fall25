#ifndef DUAL_SORT_H
#define DUAL_SORT_H

#include "QuickSortTest.h"

class DualPivotSort : public QuickSortTest {
private:
    const int LIMIT = 0;
    int partition(std::vector<int>&, int, int) override;    

public:
    DualPivotSort()  { sortType = "Dual Pivot Sort"; }
    DualPivotSort(std::vector<std::pair<char, std::vector<int>>> v) : QuickSortTest{v}{}
    ~DualPivotSort(){}

    void sort(std::vector<int>&, int, int) override;
};

#endif