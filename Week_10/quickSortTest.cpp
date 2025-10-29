#include "quickSortTest.h"

QuickSortTest::~QuickSortTest() {}

// Write results to file
void QuickSortTest::writeToFile(char type, const std::vector<std::pair<int, int>>& data)
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

// New swap function instead of standard to count swaps easier
void QuickSortTest::swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
	swaps++;
}

// Sort that may be overridden in subclasses
void QuickSortTest::sort(std::vector<int> &avector, int first, int last){
	int splitpoint = 0;	// partition splitpoint index
	if (first<last) {								  // if there is more than one element in the vector
		splitpoint = partition(avector, first, last); // partition the vector from first to last
		sort(avector, first, splitpoint - 1);		  // lower half
		sort(avector, splitpoint + 1, last);		  // upper half
	}
}

void QuickSortTest::test()
{
	// Make a copy to sort (preserve original for future tests)
    std::vector<std::pair<char, std::vector<int>>> tl = testLists;

	// Loop from LeChat(10/28/2025)
    for(auto& [listType, list] : tl) {
		//swaps = 0; // each test will run the number of types on the same object
        sort(list, 0, list.size() - 1);

        // Display results
		std::cout << "Testing " << sortType << " on " << listType << " list" << std::endl;
        std::cout << "Swaps: " << swaps << std::endl;
        std::cout << std::endl;
    }
}