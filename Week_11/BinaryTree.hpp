#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <iostream>
#include <cstdlib>

template <typename T>
class BinaryTree {

	private:
		T key;											// node's payload
		BinaryTree<T> *leftChild;						// pointer to left child
		BinaryTree<T> *rightChild;						// pointer to right child
		
		// just for illustration purposes
		void printTree(BinaryTree<T>* root, int level = 0, const std::string& prefix = "", int spacing = 4) {
			if (root) {																	// if root is not null
				if (level == 0) {														// if root is the root node
					std::cout << "Root: " << root->key << std::endl;					// print root node
				} else {																// node is not the root node
					std::string branch = (level % 2 == 1) ? "└─" : "├─";				// determine branch
					std::string spaces(spacing * level - 2, ' ');						// determine spacing
					std::cout << spaces << branch << prefix << root->key << std::endl;	// print node
				}

				if (root->leftChild || root->rightChild) {									// if node has children
					printTree(root->leftChild, level + 1, "L: ", spacing);					// print left child
					printTree(root->rightChild, level + 1, "R: ", spacing);					// print right child
				}
			}
		}

	public:
		/**
		 * @brief Construct a new Binary Tree object
		 * 
		 * @param rootObj 
		 */
		BinaryTree(T rootObj){										// constructor
			this->key = rootObj;									// set root's payload
			this->leftChild = NULL;									// set left child to null
			this->rightChild = NULL;								// set right child to null
		}

		/**
		 * @brief Destroy the Binary Tree object, created by DeepSeek (11/09/2025)
		 * 
		 */
		~BinaryTree(){
			// Recursively delete left subtree
			if (leftChild != nullptr) {
				delete leftChild;
				leftChild = nullptr;
			}
			// Recursively delete right subtree  
			if (rightChild != nullptr) {
				delete rightChild;
				rightChild = nullptr;
			}
		}

		/**
		 * @brief Insert a new node as the left child
		 * 
		 * @param newNode 
		 */
		void insertLeft(T newNode){									// insert left child
			if (this->leftChild == NULL)							// if left child is null
				this->leftChild = new BinaryTree<T>(newNode);		// create new node
			else {													// left child is not null
				BinaryTree<T> *t = new BinaryTree<T>(newNode);		// create new node
				t->leftChild = this->leftChild;						// set new node's left child to current left child
				this->leftChild = t;								// set current left child to new node
			}
		}
		
		/**
		 * @brief Insert a new node as the right child
		 * 
		 * @param newNode 
		 */
		void insertRight(T newNode){								// insert right child
			if (this->rightChild == NULL)							// if right child is null
				this->rightChild = new BinaryTree<T>(newNode);		// create new node
			else {													// right child is not null
				BinaryTree<T> *t = new BinaryTree<T>(newNode);		// create new node
				t->rightChild = this->rightChild;					// set new node's right child to current right child
				this->rightChild = t;								// set current right child to new node
			}
		}

		/**
		 * @brief Connect an existing tree as left child
		 */
		void connectLeft(BinaryTree<T>* existingTree) {
			if (this->leftChild != NULL)
				delete this->leftChild;  // Clean up existing left child
			this->leftChild = existingTree;
		}
		
		/**
		 * @brief Connect an existing tree as right child  
		 */
		void connectRight(BinaryTree<T>* existingTree) {
			if (this->rightChild != NULL)
				delete this->rightChild;  // Clean up existing right child
			this->rightChild = existingTree;
		}
		
		/**
		 * @brief Get the Right Child object
		 * 
		 * @return BinaryTree<T>* 
		 */
		BinaryTree<T> *getRightChild() { return this->rightChild; }

		/**
		 * @brief Get the Left Child object
		 * 
		 * @return BinaryTree<T>* 
		 */
		BinaryTree<T> *getLeftChild() { return this->leftChild;	}

		/**
		 * @brief Set the Root Val object (set root's payload)
		 * 
		 * @param obj 
		 */
		void setRootVal(T obj) { this->key = obj; }

		/**
		 * @brief Get the Root Val object (get root's payload)
		 * 
		 * @return T 
		 */
		T getRootVal() { return this->key; }

		/**
		 * @brief Preorder Traversal
		 * 
		 */
		void preorder(){											// preorder traversal
			std::cout << this->key << " ";							// print root
			if (this->leftChild != NULL)							// if left child is not null
				this->leftChild->preorder();						// preorder left child
			if (this->rightChild != NULL)							// if right child is not null
				this->rightChild->preorder();						// preorder right child
		}

		/**
		 * @brief Inorder Traversal
		 * 
		 */
		void inorder(){												// inorder traversal
			if (this->leftChild != NULL)							// if left child is not null
				this->leftChild->inorder();							// inorder left child
			std::cout << this->key << " ";							// print root
			if (this->rightChild != NULL)							// if right child is not null
				this->rightChild->inorder();						// inorder right child
		}

		/**
		 * @brief Postorder Traversal
		 * 
		 */
		void postorder(){											// postorder traversal
			if (this->leftChild != NULL)							// if left child is not null
				this->leftChild->postorder();						// postorder left child
			if (this->rightChild != NULL)							// if right child is not null
				this->rightChild->postorder();						// postorder right child
			std::cout << this->key << " ";							// print root
		}

		/**
		 * @brief Print Tree helper
		 * 
		 */
		void printTree() { printTree(this); }

};
#endif

