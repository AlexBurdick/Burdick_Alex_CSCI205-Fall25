#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>

// TreeNode class
template <typename T>
class TreeNode {
	public:
		T data;				// node's data. Custom instances of T should have comparison operators defined
		TreeNode* left;		// pointer to left child
		TreeNode* right;	// pointer to right child
		TreeNode(T val) : data(val), left(nullptr), right(nullptr) {}
};

template <typename T>
class BinarySearchTree {
	protected:
		TreeNode<T>* root;	// pointer to root node
		int nodeCount;		// number of nodes in the tree
		int opCount;		// track the number of comparisons and recursive calls for insterts

		// helper function with arguments to insert a node recursively - O(log n) where n is the number of nodes in the tree
		TreeNode<T>* insert(TreeNode<T>* node, T key) {			
			if (node == nullptr) {							// if node is null, create new node
				nodeCount++;  								// Only increment when actually creating a new node
				return new TreeNode<T>(key);				// return new node
			}
			
			opCount++; // Count the comparison
			if (key < node->data) {							// if key is less than node's data
				opCount++; // Count the recursive call
				node->left = insert(node->left, key);		// recursively insert key into left subtree
			} else if (key > node->data) {					// if key is greater than node's data
				opCount++; // Count the recursive call
				node->right = insert(node->right, key);		// recursively insert key into right subtree
			}
			
			// Removed increment so that the node count doesn't increase if there isn't a new node
			return node;									// return node
		}

		// helper function to find the minimum value in a subtree
		// O(log n) where n is the number of nodes in the tree
		TreeNode<T>* min(TreeNode<T>* node) {
			while (node->left != nullptr) node = node->left;
			return node;
		}

		// helper function to find the maximum value in a subtree
		// O(log n) where n is the number of nodes in the tree
		TreeNode<T>* max(TreeNode<T>* node) {
			while (node->right != nullptr) node = node->right;
			return node;
		}

		// helper function to find the inorder successor of a node
		// O(log n) where n is the number of nodes in the tree
		TreeNode<T>* remove(TreeNode<T>* node, T key) {							// args: start, key to remove
			if (node == nullptr)		return node;							// key was not found in tree
			if (key < node->data)		node->left  = remove(node->left, key);  // key is smaller than node's data, go left
			else if (key > node->data)	node->right = remove(node->right, key); // key is greater than node's data, go right
			else {																// found the node, remove it
				if (node->left == nullptr) {									// node has one child (right child))
					TreeNode<T>* temp = node->right;							// store right child
					delete node;												// delete node
					nodeCount--; // Added decrement
					return temp;												// return right child
				} else if (node->right == nullptr) {							// node has one child (left child)
					TreeNode<T>* temp = node->left;								// store left child
					delete node;
					nodeCount--; // Added decrement												// delete node
					return temp;												// return left child
				}
				// node has two children, get inorder successor
				TreeNode<T>* temp	= min(node->right);							// smallest in right subtree
				node->data			= temp->data;								// copy inorder successor's content to this node (to delete)
				node->right			= remove(node->right, temp->data);			// delete inorder successor
			}
			return node;														// return node (potentially modified)
		}

		// helper function to traverse the tree in order
		// O(n) where n is the number of nodes in the tree
		void inOrderTraversal(TreeNode<T>* node) {
			if (node != nullptr) {					// if node is not null
				inOrderTraversal(node->left);		// traverse left subtree
				std::cout << node->data << " ";		// print node's data
				inOrderTraversal(node->right);		// traverse right subtree
			}
		}

		// helper function to traverse the tree in pre-order
		// O(n) where n is the number of nodes in the tree
		void preOrderTraversal(TreeNode<T>* node) {
			if (node != nullptr) {					// if node is not null
				std::cout << node->data << " ";		// print node's data
				preOrderTraversal(node->left);		// traverse left subtree
				preOrderTraversal(node->right);		// traverse right subtree
			}
		}

		// helper function to traverse the tree in post-order
		// O(n) where n is the number of nodes in the tree
		void postOrderTraversal(TreeNode<T>* node) {
			if (node != nullptr) {					// if node is not null
				postOrderTraversal(node->left);		// traverse left subtree
				postOrderTraversal(node->right);	// traverse right subtree
				std::cout << node->data << " ";		// print node's data
			}
		}

		// just for illustration purposes
		void printTree(TreeNode<T>* root, int level = 0, const std::string& prefix = "", int spacing = 4) {
			if (root) {																	// if root is not null
				if (level == 0) {														// if root is the root node
					std::cout << "Root: " << root->data << std::endl;					// print root node
				} else {																// node is not the root node
					std::string branch = (level % 2 == 1) ? "└─" : "├─";				// determine branch
					std::string spaces(spacing * level - 2, ' ');						// determine spacing
					std::cout << spaces << branch << prefix << root->data << std::endl;	// print node
				}

				if (root->left || root->right) {										// if node has children
					printTree(root->left, level + 1, "L: ", spacing);					// print left child
					printTree(root->right, level + 1, "R: ", spacing);					// print right child
				}
			}
		}

		// Memory cleanup from DeepSeek (11/14/2025)
		void clear(TreeNode<T>* node) {
			if (node != nullptr) {
				clear(node->left);
				clear(node->right);
				delete node;
			}
		}

		// Lab assignment methods
		void flatten(TreeNode<T>* node, std::vector<int>& list) {			
			// In-order traversal
			opCount++;
			if (node != nullptr) {
				flatten(node->left, list);
				list.push_back(node->data);
				flatten(node->right, list);
			}
		}

		int closest(TreeNode<T>* node, int n) {			
			if (node == nullptr)  throw std::runtime_error("Tree is empty");

			int closestNum = node->data; // closest number in tree
			int distance = abs(n - node->data); // distance between numbers

			// Recursively check left subtree
			if (node->left != nullptr) {
				int leftClosest = closest(node->left, n);
				int leftDistance = abs(n - leftClosest);
				if (leftDistance < distance) {
					closestNum = leftClosest;
					distance = leftDistance;
				}
			}

			// Recursively check right subtree
			if (node->right != nullptr) {
				int rightClosest = closest(node->right, n);
				int rightDistance = abs(n - rightClosest);
				if (rightDistance < distance) {
					closestNum = rightClosest;
					distance = rightDistance;
				}
			}

			return closestNum;
		}

		void _find_kth_smallest(TreeNode<T>* node, int& k, T& result) {
			if (node == nullptr || k <= 0) return;

			// Traverse the left subtree, going all the way left to the smallest element
			_find_kth_smallest(node->left, k, result);

			 
			k--; 						// We've checked one node,
			if (k == 0) {				// so decrement k and check if we've found the kth smallest element
				result = node->data;	// set the result to the current node's payload
				return;
			}

			// Traverse the right subtree
			_find_kth_smallest(node->right, k, result);
		}

		int getHeight(TreeNode<T>* node) {
			if (node == nullptr) return -1; // Base case: height of an empty tree is -1

			// Recursively get the height of the left and right subtrees
			int leftHeight = getHeight(node->left);
			int rightHeight = getHeight(node->right);

			// Return the maximum height of the left and right subtrees, plus one for the current node
			return std::max(leftHeight, rightHeight) + 1;
		}

		int getBalanceFactor(TreeNode<T>* node) {
			if (node == nullptr) return 0;

			// Get the height of the left and right subtrees
			int leftHeight = getHeight(node->left);
			int rightHeight = getHeight(node->right);

			// Return the balance factor
			return leftHeight - rightHeight;
		}


	public:
		// no-arg constructor
		BinarySearchTree() : root(nullptr) {}

		// Destructor from DeepSeek (11/14/2025virtual)
		~BinarySearchTree() { this->clear(root); }

		// public insert with T argument
		virtual void insert(T key) { root = insert(root, key); }

		// public remove with T argument
		void remove(T key) { root = remove(root, key); }
		
		// getter for opCount
		int getOpCount() {
			int temp = opCount;
			this->opCount = 0; // reset op count each time so it doesn't accumulate
			return temp;
		}

		// public search with T argument
		// O(log n) where n is the number of nodes in the tree
		bool search(T key) {
			TreeNode<T>* current = root;									// start at root
			while (current != nullptr) {									// while current is not null
				if (key == current->data)		return true;				// found key
				else if (key < current->data)	current = current->left;	// key is less than current, go left
				else							current = current->right;	// key is greater than current, go right
			}
			return false;													// key not found
		}

		// public in-order traversal, no arguments
		void in_order() {
			inOrderTraversal(root);							// call private recursive helper
			std::cout << std::endl;							// new line
		}

		// public pre-order traversal, no arguments
		void pre_order() {
			preOrderTraversal(root);						// call private recursive helper
			std::cout << std::endl;
		}

		// public post-order traversal, no arguments
		void post_order() {
			postOrderTraversal(root);						// tcall private recursive helper
			std::cout << std::endl;
		}

		// Helper functions
		int size() const { return nodeCount; }	// Added a way to get nodeCount
		void print() { printTree(root); }		// public print with no arguments
		T min() { return min(root)->data; }		// public min with no arguments
		T max() { return max(root)->data; }		// public max with no arguments

		// Helpers for lab assignment methods
		void flatten(std::vector<int>& list) {
			flatten(root, list);
		}

		int closest(int n) { return closest(root, n); }

		T find_kth_smallest(int k) {
			T result; // will pass by reference in case T is a large object
			_find_kth_smallest(root, k, result);
			return result;
		}

		int height() { return getHeight(root) + 1; }

		int balance_factor() { return getBalanceFactor(root); }
};

#endif