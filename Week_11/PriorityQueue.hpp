#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include "MinHeap.hpp"
#include "BinaryTree.hpp"

class PriorityQueue : public MinHeap<BinaryTree<std::pair<char, int>>*> {
    
    private:
        
        // Returns true if first param is greater or equal to second param
        bool compareCounts(BinaryTree<std::pair<char, int>>* a, 
                           BinaryTree<std::pair<char, int>>* b) {
            return a->getRootVal().second >= b->getRootVal().second;
        }

        // Move an element up the tree to maintain the min heap property
        virtual void sift_up(int index) override {
            while (index > 1) {
                // Parent is index interger divide by 2
                int parent = index / 2;

                // If the child is greater or equal to parent, stop loop
                if (compareCounts(this->heap[index], this->heap[parent])) {
                    break;
                } else {
                    // Swap child and parent
                    std::swap(this->heap[index], this->heap[parent]);
                }
                
                // Parent is next index to test
                index = parent;
            }
        }

        // Move an element down the tree to maintain the min heap property
        void sift_down(int index) override {
            int leftChild = 2 * index;
            int rightChild = 2 * index + 1;
            int smallest = index;

            // Find the smallest child using frequency comparison
            if (leftChild < this->heap.size() && 
                !compareCounts(this->heap[leftChild], this->heap[smallest])) {
                smallest = leftChild;
            }
            if (rightChild < this->heap.size() && 
                !compareCounts(this->heap[rightChild], this->heap[smallest])) {
                smallest = rightChild;
            }

            if (smallest != index) {
                std::swap(this->heap[index], this->heap[smallest]);
                sift_down(smallest);
            }
        }

    public:

        // Constructors
        PriorityQueue() : MinHeap<BinaryTree<std::pair<char, int>>*>() {}
        ~PriorityQueue() {
            // Skip index 0 (dummy) and delete only actual trees
            if (!this->heap.empty()) {
                for (int i = 1; i < this->heap.size(); i++) {
                    delete this->heap[i];
                }
            }
        }

        // Expected Member Functions
        void enqueue(BinaryTree<std::pair<char, int>>* tree) {
            this->heap.push_back(tree);
            sift_up(this->heap.size() - 1);
        }

        BinaryTree<std::pair<char, int>>* dequeue() {
            return this->extract_min();
        }
        
        BinaryTree<std::pair<char, int>>* peek() { return this->get_min(); }

        int size() { return heap.size() - 1; }
    };

#endif