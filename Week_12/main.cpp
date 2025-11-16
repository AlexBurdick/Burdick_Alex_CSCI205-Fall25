/* Binary Search Trees
Compare binary search tree to hash tables, sorted arrays (look up binary search)
Usually used for indexing a database (uses BTREE)
Binary Search Tree Property = left child < root, right child > root
Maintain lexical ordering (ascending, descending)
If you do a traversal (in order), you will get things in order
Insert = O(log N)
lookup = O(log N)
Efficient for finding minimum (leftmost node), in order traversal
Best case for BST is root is the median
Binary search trees can become unbalanced
Insert starts at root, goes left if smaller than root, right if bigger

g++ -g -Wall -pedantic -o a.out *.cpp *.hpp *.h
valgrind --tool=memcheck --leak-check=full ./a.out
*/

#include <iostream>
#include <fstream>
#include <vector>
#include "AVLSearchTree.hpp"
#include "BinarySearchTree.hpp"

using namespace std;

vector<int> generate_vector(int, char);

int main() {
//===========================
// TASK TWO
//===========================
    // FLATTEN TREES    
    // Create test trees
    const size_t SIZE = 15;
    BinarySearchTree<int> averageBST;
    BinarySearchTree<int> worstBST;

    // fill with random numbers
	srand(time(nullptr));
	for (size_t i = 1; i <= SIZE; i++) { 
		averageBST.insert(rand() % 90 + 10);
    }
	// degrade BST to O(n) operations with this input
	for (size_t i = 1; i <= SIZE; i++) {
	    worstBST.insert(i);
    }
    
    vector<int> averageList(SIZE);
    vector<int> worstList(SIZE);
    averageBST.flatten(averageList);
    worstBST.flatten(worstList);

    // GRAPH RESULTS (write files for graphs)
    // Average case test
    ofstream averageFile("BST_Average_Case.txt");
    if (averageFile.is_open()) {
        for (size_t i = 0; i <= 1000; i+=10) {
            BinarySearchTree<int> bst;
            for (size_t j = 0; j <= i; j++) { 
                bst.insert(rand() % 90 + 10);
            }
            averageFile << i << " " << bst.getOpCount() << endl;
        }
    } else {
        cout << "Unable to open file" << endl;
    }
    averageFile.close();

    // Worst case test
    ofstream worstFile("BST_Worst_Case.txt");
    if (worstFile.is_open()) {
        for (size_t i = 0; i <= 1000; i+=10) {
            BinarySearchTree<int> bst;
            for (size_t j = 0; j <= i; j++) { 
                bst.insert(j);
            }
            worstFile << i << " " << bst.getOpCount() << endl;
        }
    } else {
        cout << "Unable to open file" << endl;
    }
    worstFile.close();

	// Call Python graphing utility
    system("python grapher.py");

    // CLOSEST TEST
    BinarySearchTree<int> bst;
    std::vector<int> vec = { 50, 30, 20, 40, 70, 60, 65, 80 };
    for (size_t i = 0; i < vec.size(); i++)
		bst.insert(vec[i]);
    
    int testNum = 43;
    int closest = bst.closest(testNum);
    cout << "Closest is: " << closest << endl;

//===========================
// TASK THREE
//===========================
/*
    AVLSearchTree<int> avl;
    std::vector<int> temp = { 50, 30, 20, 40, 70, 60, 65, 80 , 1, 4, 34, 101, 99, 45,
                                55, 22, 28, 49, 61, 36, 48, 56, 81, 72, 24, 11, 12};
    for (size_t i = 0; i < temp.size(); i++)
		avl.insert(temp[i]);
    cout << "AVL Search Tree" << endl;
    avl.print();
    cout << endl;
*/

    return 0;
}

// generates a random vector of size "size" with type "type"
//  type = 'a' for ascending, 'd' for descending, 'r' for random, 'p' for partially sorted
vector<int> generate_vector(int size, char type) {
	vector<int> temp(size);
	
	switch (type){
		case 'a': // ascending
			for(int i = 0; i < size; i++)
				temp[i] = i + 1;
			break;
		case 'd': // descending
			for(int i = 0; i < size; i++)
				temp[i] = size - i;
			break;
		case 'r': // random
			for(int i = 0; i < size; i++)
				temp[i] = rand() % 100;
			break;
		case 'p': // partially sorted
			for(int i = 0; i < size; i++)
				temp[i] = i + 1;
			// swap every 5th item
			for (size_t i = 4; i < temp.size(); i += 5) 
				swap(temp[i], temp[i - 4]);
	}
	return temp;
}