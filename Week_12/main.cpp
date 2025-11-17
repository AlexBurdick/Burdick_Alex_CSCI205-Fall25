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
#include <algorithm>
#include "AVLSearchTree.hpp"
#include "BinarySearchTree.hpp"

using namespace std;

// Function prototypes
void print_vector(vector<int>&);
void flattenTrees();
void closestTest();
void graphCases();
bool is_Valid(BinarySearchTree<int>&);
BinarySearchTree<int> generate(const std::vector<int>&);
void otherTests();
void testAVL();

int main() {
    // TASK TWO
    //flattenTrees();
    //closestTest();
    //graphCases();
    //otherTests();
    //testAVL();

    return 0;
}

void flattenTrees() {
    // Create test trees
    const size_t SIZE = 15;
    BinarySearchTree<int> averageBST;
    BinarySearchTree<int> worstBST;

    // fill with random numbers
	srand(time(nullptr));
	for (size_t i = 1; i <= SIZE; i++) averageBST.insert(rand() % 90 + 10);
	
    // degrade BST to O(n) operations with this input
	for (size_t i = 1; i <= SIZE; i++) worstBST.insert(i);
    
    // Flatten to vectors
    vector<int> averageList;
    vector<int> worstList;
    int aveCount = averageBST.flatten(averageList);
    int worstCount = worstBST.flatten(worstList);
    
    // Print results
    cout << "Average List: " << endl;
    print_vector(averageList);
    cout << "Worst Case List: " << endl;
    print_vector(worstList);
}

void print_vector(vector<int>& vec) {
	for (unsigned int i = 0; i < vec.size(); i++)
		cout<< vec[i] << " ";
	cout << endl;
}

void closestTest() {
    BinarySearchTree<int> bst;
    std::vector<int> vec = { 50, 30, 20, 40, 70, 60, 65, 80 };
    for (size_t i = 0; i < vec.size(); i++)
		bst.insert(vec[i]);
    
    int testNum = 43;
    int closest = bst.closest(testNum);
    cout << "Closest is: " << closest << endl;
}

void graphCases() {
    // Average case test
    ofstream averageFile("BST_Average_Case.txt");
    BinarySearchTree<int> abst;
    if (averageFile.is_open()) {
        for (size_t i = 0; i <= 100; i++) {
            BinarySearchTree<int> abst;  // Create a new tree for each problem size
            for (size_t j = 0; j < i; j++) {
                abst.insert(rand() % 10000 + 1);
            }
            averageFile << i << " " << abst.getOpCount() << endl;
        }
    } else {
        cout << "Unable to open file" << endl;
    }
    averageFile.close();

    // Worst case test
    ofstream worstFile("BST_Worst_Case.txt");
    ofstream flattenFile("Flatten_Worst_Case.txt");
    BinarySearchTree<int> wbst;
    if (worstFile.is_open()) {
        for (size_t i = 0; i <= 100; i++) {
            BinarySearchTree<int> wbst;  // Create a new tree for each problem size
            for (size_t j = 0; j < i; j++) {
                wbst.insert(j);
            }
            worstFile << i << " " << wbst.getOpCount() << endl;

            if (flattenFile.is_open()) {
                vector<int> worstList;
                int worstCount = wbst.flatten(worstList);
                flattenFile << i << " " << worstCount;
            } else cout << "Unable to open file" << endl;
            flattenFile.close();
        }
    } else cout << "Unable to open file" << endl;
    worstFile.close();

	// Call Python graphing utility
    system("python grapher.py");
}

bool is_Valid(BinarySearchTree<int>& bst) {
    std::vector<int> vec;
    bst.flatten(vec);
    
    // Check if the flattened list is sorted
    for (size_t i = 1; i < vec.size(); i++)
        if (vec[i] <= vec[i-1]) return false;
    
    return true;
}

// Generate
void _generate(BinarySearchTree<int>& bst, const vector<int>& v) {
    if (v.empty()) return; // Validation
    
    vector<int> sortedList = v;
    sort(sortedList.begin(), sortedList.end()); // Sort list

    // Add median to tree
    int medianIndex = static_cast<int>(sortedList.size()) / 2;
    int median = sortedList[medianIndex];
    bst.insert(median);

    // Base case list size is one
    if (sortedList.size() <= 1) return;
    
    // Create left and right sublists
    vector<int> leftList(sortedList.begin(), sortedList.begin() + medianIndex);
    vector<int> rightList(sortedList.begin() + medianIndex + 1, sortedList.end());
    
    // Recursively generate left and right subtrees
    _generate(bst, leftList);
    _generate(bst, rightList);
}

// Generate helper function
BinarySearchTree<int> generate(const vector<int>& v) {
    BinarySearchTree<int> bst;
    _generate(bst, v);
    return bst;
}

void otherTests() {
    // Test generate, is_valid, kth smallest element, height, balance_factor
    std::vector<int> vec = { 50, 30, 20, 40, 70, 60, 65, 80 };
    BinarySearchTree<int> bst = generate(vec);
    if (is_Valid(bst))  cout << "Valid" << endl;
    else                cout << "Invalid" << endl;
    bst.print();
    
    cout << "2th element = " << bst.find_kth_smallest(2) << endl;
    cout << "Height = " << bst.height() << endl;
    cout << "Balance Factor = " << bst.balance_factor() << endl;
}

void testAVL() {
    AVLSearchTree<int> avl;
    vector<int> temp = { 50, 30, 20, 40, 70, 60, 65, 80 , 1, 4, 34, 101, 99, 45,
                         55, 22, 28, 49, 61, 36, 48, 56, 81, 72, 24, 11, 12};
    for (size_t i = 0; i < temp.size(); i++)
		avl.insert(temp[i]);
    cout << "AVL Search Tree" << endl;
    avl.print();
    cout << endl;
}
