#ifndef DUAL_SORT_H
#define DUAL_SORT_H

#include "CutoffInsertionSort.h"

class DualPivotSort : public CutoffInsertionSort {
private:
    int partition(std::vector<int>&, int, int) override;

public:
    DualPivotSort(std::vector<std::pair<char, std::vector<int>>>);
    ~DualPivotSort();

	void sort(std::vector<int>&, int, int) override;
};

#endif