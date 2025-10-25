#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class BubbleSort : public SortAlgorithm {
public:
    BubbleSort() {
        name = "BUBBLE_SORT";
    }

    /*
	apply the bubble sort to a vector
	maintain invariant of all indices > passnum being sorted
	Compare a pair of adjacent items (a, b),
	Swap that pair if the items are out of order (in this case, when a > b),
	Repeat Step 1 and 2 until we reach the end of array
	(the last pair is the (N-2)-th and (N-1)-th items as we use 0-based indexing),
	By now, the largest item will be at the last position.
	We then reduce N by 1 and repeat Step 1 until we have N = 1.

	Memory	= O(1)
	
	Time
	===============
	Average	= O(N^2)
	Best	= O(N) if optimized
	Worst	= O(N^2)
    */
    int sort(std::vector<int>& arr) override { // O(n ^ 2)
        int swaps = 0;
        // iterate N, N-1, N-2, N-3 . . . etc times
        for (int pass = avector.size()-1; pass > 0; pass -= 1)
            for (int i = 0; i < pass; i++)
                if (avector[i] > avector[i+1]){
                    swap(avector, i, i+1);
                    swaps++;
                }
        return swaps;
    }
};