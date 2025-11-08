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
                int parent = index / 2;
                if (compareCounts(this->heap[index], heap[parent]) break;
                std::swap(this->heap[index], this->heap[parent]);
                index = parent;
            }
        }

    public:

        PriorityQueue() : MinHeap<BinaryTree<std::pair<char, int>>*>() {}
        ~PriorityQueue() = default;

        void enqueue(BinaryTree<std::pair<char, int>>* tree) {
            this->heap.push_back(tree);
            sift_up(this->heap.size() - 1);
        }
        
        T peek() const { return this->get_min(); }
};

#endif