#ifndef AVL_SEARCH_TREE_HPP
#define AVL_SEARCH_TREE_HPP

#include "BinarySearchTree.hpp"

template <typename T>
class AVLTreeNode : public TreeNode<T> {
    public:
        AVLTreeNode* left;
        AVLTreeNode* right;
        int balanceFactor;  // height(left) - height(right)
        int height;
        
        AVLTreeNode(const T& val)
        : TreeNode<T>(val), left(nullptr), right(nullptr),
            balanceFactor(0), height(1) {}
};

template <typename T>
class AVLSearchTree : public BinarySearchTree<T> {
private:
    AVLTreeNode<T>* root; // pointer to root node

    // Override height calculation methods
    int getHeight(AVLTreeNode<T>* node) {
        return node ? node->height : 0;
    }
    
    int getBalanceFactor(AVLTreeNode<T>* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }
    
    void updateHeight(AVLTreeNode<T>* node) {
        if (node) {
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
            node->balanceFactor = getBalanceFactor(node);
        }
    }

    // just for illustration purposes
    void printTree(AVLTreeNode<T>* root, int level = 0, const std::string& prefix = "", int spacing = 4) {
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

    AVLTreeNode<T>* insert(AVLTreeNode<T>* node, T key) {
        // Standard BST insertion
        if (!node) return new AVLTreeNode<T>(key);
        
        if (key < node->data)
            node->left = insert(node->left, key);
        else if (key > node->data)
            node->right = insert(node->right, key);
        else
            return node;  // Duplicate keys not allowed
            
        // Update height and balance factor
        updateHeight(node);
        
        // Rebalance if needed
        return rebalance(node);
    }
    
    AVLTreeNode<T>* rotateLeft(AVLTreeNode<T>* x) {
        AVLTreeNode<T>* y = x->right;
        AVLTreeNode<T>* T2 = y->left;
        
        // Perform rotation
        y->left = x;
        x->right = T2;
        
        // Update heights
        updateHeight(x);
        updateHeight(y);
        
        return y;
    }
    
    AVLTreeNode<T>* rotateRight(AVLTreeNode<T>* y) {
        AVLTreeNode<T>* x = y->left;
        AVLTreeNode<T>* T2 = x->right;
        
        // Perform rotation
        x->right = y;
        y->left = T2;
        
        // Update heights
        updateHeight(y);
        updateHeight(x);
        
        return x;
    }
    
    AVLTreeNode<T>* rebalance(AVLTreeNode<T>* node) {
        int balance = getBalanceFactor(node);
        
        // Left Left Case
        if (balance > 1 && getBalanceFactor(node->left) >= 0)
            return rotateRight(node);
            
        // Left Right Case
        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        // Right Right Case
        if (balance < -1 && getBalanceFactor(node->right) <= 0)
            return rotateLeft(node);
            
        // Right Left Case
        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;  // No rotation needed
    }
    
    AVLTreeNode<T>* remove(AVLTreeNode<T>* node, T key) {
        if (!node) return node;
        
        // Standard BST deletion
        if (key < node->data)
            node->left = remove(node->left, key);
        else if (key > node->data)
            node->right = remove(node->right, key);
        else {
            // Node with only one child or no child
            if (!node->left || !node->right) {
                AVLTreeNode<T>* temp = node->left ? node->left : node->right;
                
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;

            } else {
                // Node with two children
                AVLTreeNode<T>* temp = minValueNode(node->right);
                node->data = temp->data;
                node->right = remove(node->right, temp->data);
            }
        }
        
        if (!node) return node;
        
        // Update height and rebalance
        updateHeight(node);
        return rebalance(node);
    }

    public:
        AVLSearchTree() : root(nullptr) {}
        ~AVLSearchTree() {}

        bool is_balanced() {
            if (root->balanceFactor < -1 || root->balanceFactor > 1) return true;
            else return false;
        }

        // Provide public insert that calls base class insert
        void insert(T key) override {
            this->root = insert((this->root), key);
        }

        int size() { return getHeight(root); }

        void print() { printTree(root); }

};
#endif