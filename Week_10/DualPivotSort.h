#ifndef DUAL_SORT_H
#define DUAL_SORT_H

#include "QuickSortTest.h"

class DualPivotSort : public QuickSortTest {
private:
    int partition(std::vector<int>&, int, int) override;

public:
    DualPivotSort() = default;
    DualPivotSort(std::vector<std::pair<char, std::vector<int>>>);
    ~DualPivotSort();

	void sort(std::vector<int>&, int, int) override;
};

#endif