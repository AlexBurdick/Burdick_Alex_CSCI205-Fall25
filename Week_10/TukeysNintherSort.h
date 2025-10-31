#ifndef TUKEYS_NINTHER_SORT_H
#define TUKEYS_NINTHER_SORT_H

#include "QuickSortTest.h"

class TukeysNintherSort : public QuickSortTest {
private:
    int depth = 0;
    const int MAX_DEPTH = 3;

    int ninther(std::vector<int>&, int, int);
    int partition(std::vector<int> &avector, int low, int high) override;

public:
    TukeysNintherSort() { sortType = "Tukey's Ninther Sort"; }
    TukeysNintherSort(std::vector<std::pair<char, std::vector<int>>> v) : QuickSortTest{v}{}
    ~TukeysNintherSort(){}
};

#endif