#ifndef LAZY_PIVOT_SORT_H
#define LAZY_PIVOT_SORT_H

#include "QuickSortTest.h"

class LazyPivotSort : public QuickSortTest {
private:
    int partition(std::vector<int>&, int, int) override; // Hoare partition scheme

public:
    LazyPivotSort() { sortType = "Lazy Pivot Sort"; }
    LazyPivotSort(std::vector<std::pair<char, std::vector<int>>> v) : QuickSortTest{v}{}
    ~LazyPivotSort(){}
};

#endif