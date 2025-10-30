#include "DualPivotSort.h"

DualPivotSort::DualPivotSort(std::vector<std::pair<char, std::vector<int>>> vec)
    : QuickSortTest{vec}
{
    sortType = "Cutoff_Insertion_Sort";
}

DualPivotSort::~DualPivotSort(){}

int DualPivotSort::partition(std::vector<int> &avector, int first, int last)
{
    int splitpoint = 0;
    return splitpoint;
}

void DualPivotSort::sort(std::vector<int> &avector, int first, int last)
{

}