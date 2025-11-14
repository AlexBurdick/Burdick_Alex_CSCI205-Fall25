#include "BinarySearchTree.hpp"

template <typename T>
class AVLTreeNode {
public:
    T data;
    AVLTreeNode* left;
    AVLTreeNode* right;
    AVLTreeNode* parent;
    int balanceFactor;  // height(left) - height(right)
    int height;
    
    AVLTreeNode(T val) : data(val), left(nullptr), right(nullptr), 
                         parent(nullptr), balanceFactor(0), height(1) {}
    
    bool isLeftChild() const { return parent && parent->left == this; }
    bool isRightChild() const { return parent && parent->right == this; }
    bool isRoot() const { return parent == nullptr; }
    bool hasLeftChild() const { return left != nullptr; }
    bool hasRightChild() const { return right != nullptr; }
};

template <typename T>
class AVLTree : public BinarySearchTree<T> {
private:
    using BinarySearchTree<T>::root;  // Access base class root
    
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

public:
    AVLSearchTree() = default;
    ~AVLSearchTree() {}
    
    // Override insert to maintain AVL property
    void insert(T key) override {
        root = insert(root, key);
    }
    
private:
    AVLTreeNode<T>* insert(AVLTreeNode<T>* node, T key) override {
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
    
    // Override remove method as well
    AVLTreeNode<T>* remove(AVLTreeNode<T>* node, T key) override {
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
                    *node = *temp;  // Copy contents
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
    
    AVLTreeNode<T>* minValueNode(AVLTreeNode<T>* node) {
        AVLTreeNode<T>* current = node;
        while (current->left)
            current = current->left;
        return current;
    }
};