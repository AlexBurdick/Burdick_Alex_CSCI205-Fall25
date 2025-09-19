/*********************************************************************
 * @file  Queue.hpp
 * 
 * @brief Implementation of the class Queue.
 *********************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

template <typename T>
class Queue{

    private:
        Deque<T>* d; // = new Deque<T>(10);

        void print(){
            d->print();
        }

    public:
        // CONSTRUCTORS 
        Queue(){
            d = new Deque<T>();
        };

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

        T front(){
            return d->front();
        }

        T back(){
            return d->back();
        }

        bool full(){
            return d->full();
        }

        bool empty(){
            return d->empty();
        }

        size_t size(){
            return d->size();
        }
};
#endif