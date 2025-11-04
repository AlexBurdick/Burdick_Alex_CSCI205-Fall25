#include <iostream>
#include <ctime>
#include <vector>
#include "MaxHeap.hpp"

int main() {
	MaxHeap<int> maxHeap;						// create empty max heap

	const int SIZE = 11;
	std::vector<int> temp(SIZE);				// create vector to store random numbers

	srand(time(NULL));							// seed random number generator
	for (int i = 0; i <= SIZE; i++){			// for each element in vector
		maxHeap.insert(rand() % 90 + 10);		// insert random number into empty heap
		temp[i] = rand() % 90 + 10;				// insert random number into vector
	}

	MaxHeap<int> maxHeap2(temp);				// create max heap from vector
	maxHeap2.print_tree();
	std::cout << std::endl;
	maxHeap2.print_heap();

	std::cout << std::endl;

	maxHeap.print_tree();
	std::cout << std::endl;
	maxHeap.print_heap();

	std::cout << "Maximum element: " << maxHeap.get_max() << std::endl;


	while (!maxHeap.empty()){
		std::cout << "Extracted: " << maxHeap.extract_max() << std::endl;
		maxHeap.print_tree();
		std::cin.get();		// study the displayed tree, then press enter to continue
	}
	

	return 0;
}