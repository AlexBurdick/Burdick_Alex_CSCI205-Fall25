#ifndef QUICK_SORT_TEST_H
#define QUICK_SORT_TEST_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

class QuickSortTest {
private:
	vector<char> listTypes{'a', 'd', 'r', 'p'};
	vector<pair<char, vector<int>>> testLists;
	vector<pair<int, int>> testResults;
	
	vector<int> generateList(size_t size, char type);

protected:
	string sortType {"Quick_Sort"};	// Name of sort (for printing purposes)
	int swaps {0}; 	// Counter for operations (perfomance testing)

    void writeToFile(char type, const vector<pair<int, int>>& data);
	virtual int partition(vector<int>&, int, int) = 0;

public:
	// Constructors & Destructors
	virtual ~QuickSortTest();

	// Getters
	string getSortType() const { return sortType; }
	vector<pair<char, vector<int>>> getLists() { return testLists; }

	// Member fucntions
	virtual void sort(vector<int>&, int, int);
	void test(size_t size);
};

#endif