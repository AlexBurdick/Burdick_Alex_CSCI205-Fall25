#include "QuickSortTest.h"

// Write results to file
void QuickSortTest::writeToFile(char listType, int n, int swaps)
{
	std::string filename = "test_results/" + sortType + "_" + listType + ".txt";
	std::ofstream outFile(filename, std::ios::app);
	
	if (!outFile.is_open()) {
		std::cerr << "Error: Could not open file " << filename << std::endl;
		return;
	}

	outFile << n << " " << swaps << std::endl;
	outFile.close();
}

// New swap function instead of standard to count swaps easier
void QuickSortTest::swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
	swaps++;
}

// Sort that may be overridden in subclasses
void QuickSortTest::sort(std::vector<int> &avector, int first, int last){
	int splitpoint = 0;	// partition splitpoint index
	
	if (first < last) {								  // if there is more than one element in the vector
		splitpoint = partition(avector, first, last); // partition the vector from first to last
		sort(avector, first, splitpoint - 1);		  // lower half
		sort(avector, splitpoint + 1, last);		  // upper half
	}
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
			//testResults.push_back({n, swaps});
			writeToFile(listType, n, swaps);

			// Display results
			std::cout << "Testing: " << sortType << " " << listType << std::endl;
			std::cout << "Results: " << "(" << n << " " << swaps << ")" << " " << endl;
		}
	}
}