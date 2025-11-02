#ifndef QUICK_SORT_TEST_H
#define QUICK_SORT_TEST_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "ListGenerator.hpp"

class QuickSortTest {
private:
	std::vector<std::pair<int, int>> testResults;
	std::vector<std::pair<char, std::vector<int>>> testLists;
	std::vector<char> efficiencyType{'s', 'c', 'r'};

protected:
	std::string sortType {"Quick Sort"}; // Name of sort (for printing purposes)
	int swaps		{0}; // Counter for swap operations (perfomance testing)
	int comparisons {0}; // Counter for comparison operations (performance testing)
	unsigned int recursionDepth {0};
	unsigned int maxRecursions {0};
	const int insertionLIMIT {15};

    void writeToFile(char type, int n, int swaps);
	virtual int partition(std::vector<int>&, int, int) = 0;
	void swap(int&, int&);
	void insertionSort(std::vector<int>&);

	// Setters
	void setTestLists(int size);

public:
	// Constructors & Destructors
	QuickSortTest() = default;
	QuickSortTest(std::vector<std::pair<char, std::vector<int>>> vec) : testLists{vec}{}
	virtual ~QuickSortTest(){}

	// Getters
	std::string getSortType() const { return sortType; }
	int getSwaps() const { return swaps; }
	int getComparisons() const { return comparisons; }
	int getRecursions() const { return maxRecursions; }
	std::vector<std::pair<int, int>> getTestResults() { return testResults; };

	void appendTestResults(int n, int o) { testResults.push_back({n, o}); }

	// Member fucntions
	virtual void sort(std::vector<int>&, int, int);
	void test(int size, int increment);
	void resetCounters();
};

#endif