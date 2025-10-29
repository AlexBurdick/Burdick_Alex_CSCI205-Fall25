#ifndef DUAL_SORT_H
#define DUAL_SORT_H

#include "CutoffInsertionSort.h"

class DualPivotSort : public QuickSortTest {
private:
    int partition(std::vector<int>&, int, int) override;

public:
    DualPivotSort(vector<pair<char, vector<int>>>);
    ~DualPivotSort();

	void sort(std::vector<int>&, int, int) override;
};

#endif