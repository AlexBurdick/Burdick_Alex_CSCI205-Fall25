#ifndef QUICK_SORT_TEST_H
#define QUICK_SORT_TEST_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ListGenerator.hpp"

class QuickSortTest {
private:
	std::vector<std::pair<int, int>> testResults;
	std::vector<std::pair<char, std::vector<int>>> testLists;

protected:
	std::string sortType {"Quick Sort"}; // Name of sort (for printing purposes)
	int swaps {0}; 	// Counter for operations (perfomance testing)

    void writeToFile(char type, const std::vector<std::pair<int, int>>& data);
	virtual int partition(std::vector<int>&, int, int) = 0;
	void swap(int&, int&);

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

	// Member fucntions
	virtual void sort(std::vector<int>&, int, int);
	void test(int size, int increment);
};

#endif