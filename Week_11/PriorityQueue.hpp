#include <string>
#include "MinHeap.hpp"

template <typename T>
class PriorityQueue : MinHeap {
    public: 
        void enqueue(T value)   { insert(T value); }
        T dequeue()             { return extract_min(); }
        
};