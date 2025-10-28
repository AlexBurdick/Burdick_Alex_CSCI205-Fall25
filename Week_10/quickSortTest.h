#ifndef QUICK_SORT_TEST_H
#define QUICK_SORT_TEST_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class QuickSortTest {
private:
	std::string sortType {"Quick_Sort"};	// Name of sort (for printing purposes)
	std::vector<int> list;					// List to be sorted

protected:
	int swaps {0}; // Counter for operations (perfomance testing)

	// Setters
    void setSortType(const std::string& type) { sortType = type; }	// Allow subclasses to modify sortType
	void setList(std::vector<int> &avector) { list = avector; }		// Allow subclasses to modify list

	// Utility methods
    void writeToFile(const std::vector<std::vector<int>>& data);	// Writes results of test to file
	
	// Helper methods
	void swap(int&, int&);											// Helper method for sorts
	virtual int partition(std::vector<int>&, int, int) = 0;			// Partitioning to be overridden

public:
	// Constructors & Destructors
	virtual ~QuickSortTest();

	// Member fucntions
	virtual int sort(std::vector<int>&, int, int);
	int sort(std::vector<int>&);

	// Getters
	std::string getSortType() const { return sortType; }
};

#endif