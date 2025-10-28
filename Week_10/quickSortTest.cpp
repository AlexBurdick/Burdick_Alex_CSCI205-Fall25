#include "quickSortTest.h"

// Destructor
QuickSortTest::~QuickSortTest() {}

// Private memeber functions
// Write to file (from LeChat, 10/22/2025)
void QuickSortTest::writeToFile(const std::vector<std::vector<int>>& data)
{
	std::string filename = sortType + ".txt";
	std::ofstream outFile(filename);
	if (!outFile.is_open()) {
		std::cerr << "Error: Could not open file " << filename << std::endl;
		return;
	}

	for (std::vector<int> nums : data)
		outFile << nums[0] << " " << nums[1] << std::endl;
	
	outFile.close();
}

// Sort that will be overridden in some subclasses
int QuickSortTest::sort(std::vector<int> &avector, int first, int last) {
	int splitpoint = 0;	// partition splitpoint index

	if (first<last) {									// if there is more than one element in the vector
		splitpoint = partition(avector, first, last);	// partition the vector from first to last
		//splitpoint = partition2(avector, first, last);
		sort(avector, first, splitpoint - 1);		// lower half
		sort(avector, splitpoint + 1, last);		// upper half
	}

	return swaps;
}

// Helper function to call the sort function without parameters
int QuickSortTest::sort(std::vector<int> &avector)
{
    int first = avector[0];
	int last  = avector[avector.size()-1];
	return sort(avector, first, last);
}