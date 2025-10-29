#include "quickSortTest.h"

QuickSortTest::~QuickSortTest() {}

vector<int> QuickSortTest::generateList(size_t size, char type)
{
	std::vector<int> vec(size);
	
	switch(type)
	{
		case 'a': // Ascending
			for(int i = 0; i < size; i++)
				vec[i] = i + 1;
			break;

		case 'd': // Descending
			for(size_t i = 0; i < size; i++)
				vec[i] = size - i;
			break;

		case 'r': // Random
			for(size_t i = 0; i < size; i++)
				vec[i] = rand() % 100;
			break;

		case 'p': // Partially sorted
			for(size_t i = 0; i < size; i++)
				vec[i] = i + 1;
			// Swap every 5th item
			for (size_t i = 4; i < vec.size(); i += 5)
				std::swap(vec[i], vec[i-4]);
	}
	
	return vec;
}

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
void QuickSortTest::sort(std::vector<int> &avector, int first, int last){
	int splitpoint = 0;	// partition splitpoint index

	if (first<last) {								  // if there is more than one element in the vector
		splitpoint = partition(avector, first, last); // partition the vector from first to last
		sort(avector, first, splitpoint - 1);		  // lower half
		sort(avector, splitpoint + 1, last);		  // upper half
	}
}

void QuickSortTest::test(size_t size)
{
	// Create new lists for testing
	for(char type : listTypes)
		testLists.push_back({type, generateList(size, type)});

	// Loop from LeChat(10/28/2025)
    for(auto& [listType, list] : testLists) {
        // Sort the data
		//swaps = 0; // Reset swaps count before each test
        sort(list, 0, list.size() - 1);

        // Display results
		cout << "Testing " << sortType << " on " << listType << " list" << endl;
        cout << "Swaps: " << swaps << endl;
        cout << endl;
    }
}