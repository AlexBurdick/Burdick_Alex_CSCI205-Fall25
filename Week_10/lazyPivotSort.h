#ifndef LAZY_PIVOT_SORT_H
#define LAZY_PIVOT_SORT_H

#include "quickSortTest.h"

class lazyPivotSort : public quickSortTest {
private:
    int partition(std::vector<int>&, int, int) override;

public:
    lazyPivotSort(std::vector<int>&);
    ~lazyPivotSort();
};

#endif