#ifndef TUKEYS_NINTHER_SORT_H
#define TUKEYS_NINTHER_SORT_H

#include "MedianOf3Sort.h"

class TukeysNintherSort : public MedianOf3Sort {
private:
    int ninther(std::vector<int>&, int, int);

public:
    TukeysNintherSort();
    ~TukeysNintherSort();
};

#endif