#include "quickSortTest.h"

QuickSortTest::~QuickSortTest() {}

// Write results to file
void QuickSortTest::writeToFile(char type, const vector<pair<int, int>>& data)
{
	std::string filename = sortType + ".txt";
	std::ofstream outFile(filename);

	if (!outFile.is_open()) {
		std::cerr << "Error: Could not open file " << filename << std::endl;
		return;
	}

	for(auto& [n, swaps] : testResults)
		outFile << n << " " << swaps << std::endl;
	
	outFile.close();
}

// Sort that may be overridden in subclasses
void QuickSortTest::sort(vector<int> &avector, int first, int last){
	int splitpoint = 0;	// partition splitpoint index
	if (first<last) {								  // if there is more than one element in the vector
		splitpoint = partition(avector, first, last); // partition the vector from first to last
		sort(avector, first, splitpoint - 1);		  // lower half
		sort(avector, splitpoint + 1, last);		  // upper half
	}
}

void QuickSortTest::test()
{

	// Make a copy to sort (preserve original)
    vector<pair<char, vector<int>>> tl = testLists;

	// Loop from LeChat(10/28/2025)
    for(auto& [listType, list] : tl) {
        // Sort the data
		//swaps = 0; // Reset swaps count before each test
        sort(list, 0, list.size() - 1);

        // Display results
		cout << "Testing " << sortType << " on " << listType << " list" << endl;
        cout << "Swaps: " << swaps << endl;
        cout << endl;
    }
}