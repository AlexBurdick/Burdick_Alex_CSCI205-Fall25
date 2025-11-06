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
};

#endif