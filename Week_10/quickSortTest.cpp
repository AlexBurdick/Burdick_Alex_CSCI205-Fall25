#include "QuickSortTest.h"

// Write results to file
void QuickSortTest::writeToFile(char listType, int n, int ops)
{
	std::string filename = "test_results/" + sortType + "_" + listType + ".txt";
	std::ofstream outFile(filename, std::ios::app);
	
	if (!outFile.is_open()) {
		std::cerr << "Error: Could not open file " << filename << std::endl;
		return;
	}

	outFile << n << " " << ops << std::endl;
	outFile.close();
}

void QuickSortTest::resetCounters()
{
    	swaps = 0;
    	comparisons = 0;
		recursionDepth = 0;
		maxRecursions = 0;
}

// New swap function instead of standard to count swaps easier
void QuickSortTest::swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
	swaps++;
}

/*
Switch to insertion sort for arrays with size less than a pre-decided limit. Once the 
size of the sub-array goes lower than the limit, apply insertion sort on that sub-array.
*/
void QuickSortTest::insertionSort(std::vector<int> &avector)
{
    for (unsigned int index = 1; index<avector.size(); index++) {
        int current		 = avector[index];			// remember current item
        unsigned int pos = index;					// need current position to move towards front
        while (pos>0 && avector[pos-1]>current) {	// while not at front and current item is less than previous
            swap(avector[pos], avector[pos-1]);		// shift by 1 spot
            pos--; 									// keep moving towards front of vector
        }
        avector[pos] = current;						// place current item in opened spot
    }
}

// Sort that may be overridden in subclasses
void QuickSortTest::sort(std::vector<int> &avector, int first, int last){
	recursionDepth++;
	maxRecursions = max(maxRecursions, recursionDepth);
	
	if( (last - first + 1) <= insertionLIMIT )
    {
        // Extract the subarray from first to last
        std::vector<int> subvector(avector.begin() + first, avector.begin() + last + 1);
        insertionSort(subvector);
        // Copy the sorted subarray back to the original vector
        std::copy(subvector.begin(), subvector.end(), avector.begin() + first);
		recursionDepth--;
		return;
    }
	
	int splitpoint = 0;	// partition splitpoint index
	if (first < last) {						  // if there is more than one element in the vector
		splitpoint = partition(avector, first, last); // partition the vector from first to last
		sort(avector, first, splitpoint - 1);		  // lower half
		sort(avector, splitpoint + 1, last);		  // upper half
	}

	recursionDepth--;
}

// Setters
void QuickSortTest::setTestLists(int size)
{
	ListGenerator lg(size);
	testLists = lg.getLists();
}

void QuickSortTest::test(int size, int increment)
{
	for(int n = 0; n <= size; n += increment)
	{
		// Create lists to be sorted [a, d, r, p]
		setTestLists(n);
		// Make a copy to sort (preserve original for future tests)
    	std::vector<std::pair<char, std::vector<int>>> tl = testLists;
		
		// Loop from LeChat(10/28/2025)
		for(auto& [listType, list] : tl)
		{
			swaps = 0; // each test will run the number of types on the same object
			sort(list, 0, list.size() - 1);
			//writeToFile(listType, n, maxDepth);

			// Display results
			std::cout << "TESTING - " << sortType << " " << listType << std::endl;
			std::cout << "Swaps: 			" << "(" << n << " " << swaps << ")\n";
			std::cout << "Comparisons:		" << "(" << n << " " << comparisons << ")\n";
			std::cout << "Recursion depth:	" << "(" << n << " " << maxRecursions << ")\n";
		}
	}
}