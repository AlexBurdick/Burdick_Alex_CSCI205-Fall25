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

        // Move an element down the tree to maintain the min heap property: O(log n)
        void sift_down(int index) {
            int leftChild   = 2 * index;							// get left child index
            int rightChild  = 2 * index + 1;						// get right child index
            int largest     = index;								// set largest to index

            // find the lergest child
            if (leftChild < heap.size() && heap[leftChild] < heap[largest])		// if left child is less than largest
                largest = leftChild;											// set largest to left child

            if (rightChild < heap.size() && heap[rightChild] < heap[largest])	// if right child is less than largest
                largest = rightChild;											// set largest to right child

            if (largest != index) {									// if largest is at index
                std::swap(heap[index], heap[largest]);				// swap element and largest
                sift_down(largest);									// recursively sift down largest
            }
        }

    public:

        // Constructors
        PriorityQueue() : MinHeap<BinaryTree<std::pair<char, int>>*>() {}
        ~PriorityQueue() = default;

        // Expected Member Functions
        void enqueue(BinaryTree<std::pair<char, int>>* tree) {
            this->heap.push_back(tree);
            sift_up(this->heap.size() - 1);
        }

        BinaryTree<std::pair<char, int>>* dequeue() {
            return this->extract_min();
        }
        
        BinaryTree<std::pair<char, int>>* peek() { return this->get_min(); }
    };

#endif