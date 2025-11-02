#ifndef MERGE_H
#define MERGE_SORT_H

#include "QuickSortTest.h"

class MergeSort : public QuickSortTest {
private:
    int partition(std::vector<int>&, int, int) override;
    vector<int> mergeSort(vector<int>);
    void merge(vector<int>&, vector<int>, vector<int>);

public:
    MergeSort() { sortType = "Merge Sort"; }
    MergeSort(std::vector<std::pair<char, std::vector<int>>> v) : QuickSortTest{v}{}
    ~MergeSort(){}

    void sort(std::vector<int>&, int, int) override;
};

#endif