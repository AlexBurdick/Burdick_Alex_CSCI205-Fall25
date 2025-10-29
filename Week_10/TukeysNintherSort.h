#ifndef TUKEYS_NINTHER_SORT_H
#define TUKEYS_NINTHER_SORT_H

#include "MedianOf3Sort.h"

class TukeysNintherSort : public MedianOf3Sort {
private:
    int ninther(std::vector<int>&, int, int);

    int partition(std::vector<int>&, int, int);

public:
    TukeysNintherSort(std::vector<std::pair<char, std::vector<int>>>);
    ~TukeysNintherSort();
};

#endif