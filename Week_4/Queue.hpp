/*********************************************************************
 * @file  Queue.hpp
 * 
 * @brief Implementation of the class Queue.
 *********************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include "Deque.hpp"

template <typename T>
class Queue{

    private:
        Deque<T>* d; // = new Deque<T>(10);

    public:
        // CONSTRUCTORS 
       // Queue() = default;

        Queue(size_t cap){
            d = new Deque<T>(cap);
        }

        // MEMBER FUNCTIONS
        void enqueue(const T& item){
            d->push_front(item);
        }

        T dequeue(){
            return d->pop_back();
        }

        const T& peak() const{
            return d->front();
        }

        bool empty(){
            return d->empty();
        }

        size_t size(){
            return d->size();
        }

        void print(){
            d->print();
        }
};
#endif