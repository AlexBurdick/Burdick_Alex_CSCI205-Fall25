#ifndef DUAL_SORT_H
#define DUAL_SORT_H

#include "CutoffInsertionSort.h"

class DualPivotSort : public QuickSortTest {
private:
    int partition(std::vector<int>&, int, int) override;

public:
    DualPivotSort();
    ~DualPivotSort();

	void sort(std::vector<int>&, int, int) override;
};

#endif