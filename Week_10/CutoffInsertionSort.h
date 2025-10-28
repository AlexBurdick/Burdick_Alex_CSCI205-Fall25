#ifndef MEDIAN_OF_3_SORT_H
#define MEDIAN_OF_3_SORT_H

#include "QuickSortTest.h"

class CutoffInsertionSort : public QuickSortTest {
private:        
    int partition(std::vector<int>& avector, int first, int last) override;

protected:
    // Limit varies from system to system and typically it is between 5 to 27
    const int limit = 27;
    
    int insertionSort(std::vector<int>&);
    
public:
    CutoffInsertionSort(std::vector<int>&);
    ~CutoffInsertionSort();

	int sort(std::vector<int>&, int, int);
};

#endif