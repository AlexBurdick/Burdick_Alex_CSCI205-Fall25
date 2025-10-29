#ifndef LAZY_PIVOT_SORT_H
#define LAZY_PIVOT_SORT_H

#include "QuickSortTest.h"

class LazyPivotSort : public QuickSortTest {
private:
    int partition(std::vector<int>&, int, int) override; // Hoare partition scheme

public:
    LazyPivotSort(vector<pair<char, vector<int>>>);
    ~LazyPivotSort();
};

#endif