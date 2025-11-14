/*  g++ -g -Wall -pedantic -o a.out *.cpp *.hpp *.h
    valgrind --tool=memcheck --leak-check=full ./a.out
*/

#include <iostream>
#include <ctime>
#include <vector>
#include "AVLTree.hpp"

/* Binary search trees
Compare binary search tree to hash tables, sorted arrays (look up binary search)
Usually used for indexing a database (uses BTREE)
Binary Search Tree Property = left child < right child
Maintain lexical ordering (ascending, descending)
If you do a traversal (in order), you will get things in order
Insert = O(log N)
lookup = O(log N)
Efficient for finding minimum (leftmost node), in order traversal
Best case for BST is root is the median
Binary search trees can become unbalanced
Insert starts at root, goes left if smaller than root, right if bigger
*/
int main() {
    // AVL bst
    AVLTree<int> avl;
    std::vector<int> temp = { 50, 30, 20, 40, 70, 60, 65, 80 };
    for (size_t i = 0; i < temp.size(); i++)
		avl.insert(temp[i]);
    avl.print();
    
    // bst
    BinarySearchTree<int> bst;
	// use this data to test remove
	std::vector<int> temp = { 50, 30, 20, 40, 70, 60, 65, 80 };
	for (size_t i = 0; i < temp.size(); i++)
		bst.insert(temp[i]);
	bst.print();
    /*
	// demo different traversals
	std::cout << "In-order traversal: ";
	bst.in_order();
	std::cout << "Pre-order traversal: ";
	bst.pre_order();
	std::cout << "Post-order traversal: ";
	bst.post_order();
	// search
	if (bst.search(60)) std::cout << "Found 60 in the BST." << std::endl;
	else std::cout << "60 not found in the BST." << std::endl;
	// remove an item
	std::cout << "Before removing 50" << std::endl;
	bst.print();
	std::cout << "After removing 50" << std::endl;
	bst.remove(50);
	bst.print();
	*/
    /*
	// fill with random numbers
    const size_t SIZE = 10;
	srand(time(nullptr));
	for (int i = 0; i < SIZE; i++)
		bst.insert(rand() % 90 + 10);
	// degrade BST to O(n) operations with this input
	for (int i = 1; i <= SIZE; i++)
	    bst.insert(i);
    */

    return 0;
}