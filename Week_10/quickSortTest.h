#ifndef QUICK_SORT_TEST_H
#define QUICK_SORT_TEST_H

#include <vector>

int quickSort(std::vector<int> &avector, int first, int last);
int partition(std::vector<int> &avector, int first, int last);
int partition2(std::vector<int> &avector, int low, int high);
int medianOf3(std::vector<int> &v, int left, int right);

#endif