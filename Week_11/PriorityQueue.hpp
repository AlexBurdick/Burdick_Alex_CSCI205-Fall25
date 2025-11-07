#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include "MinHeap.hpp"

template <typename T>
class PriorityQueue : public MinHeap<T> {
    
    public:

        PriorityQueue()  = default;
        ~PriorityQueue() = default;

        void enqueue(const T& value) {
            this->insert(value);
        }
        
        T peek() const {
            return this->get_min();
        }

        // Returns true if first param is less that second param
        bool compareCounts(BinaryTree<std::pair<char, int>>* a, 
                            BinaryTree<std::pair<char, int>>* b) {
            return a->getRootVal().second < b->getRootVal().second;
        }
};

#endif