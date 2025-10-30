#ifndef CUTOFF_INSERTION_SORT_H
#define CUTOFF_INSERTION_SORT_H

#include "QuickSortTest.h"

class CutoffInsertionSort : public QuickSortTest {
private:        
    int partition(std::vector<int>& avector, int first, int last) override;

protected:
    std::string sortType = "Cutoff Insertion Sort";
    const int limit = 5; // Limit varies from system to system and typically it is between 5 to 27
    void insertionSort(std::vector<int>&);
    
public:
    CutoffInsertionSort() = default;
    CutoffInsertionSort(std::vector<std::pair<char, std::vector<int>>> v) : QuickSortTest{v}{}
    ~CutoffInsertionSort(){}

	void sort(std::vector<int>&, int, int);
};

#endif