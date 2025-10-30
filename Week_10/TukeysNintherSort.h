#ifndef TUKEYS_NINTHER_SORT_H
#define TUKEYS_NINTHER_SORT_H

#include "QuickSortTest.h"

class TukeysNintherSort : public QuickSortTest {
private:
    int ninther(std::vector<int>&, int, int);
    int TukeysNintherSort::partition(std::vector<int> &avector, int low, int high) override;

public:
    TukeysNintherSort() = default;
    TukeysNintherSort(std::vector<std::pair<char, std::vector<int>>>);
    ~TukeysNintherSort();
};

#endif