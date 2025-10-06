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
        Deque<T> d;

    public:
        // CONSTRUCTORS 
        /**
		 * @brief Default constructor.
		 * 
\		 */
        Queue()

        /**
		 * @brief Construct a new Queue object with a given capacity
		 * 
		 * @param cap The capacity of the stack
		 */
        Queue(size_t cap){
            d = Deque<T>(cap);
        }

        /**
		 * @brief Explicity delete copy constructor
		 * 
		 */
        Queue(const Queue&) = delete;

        // MEMBER FUNCTIONS
        void enqueue(const T& item) d.push_front(item);
        T dequeue()                 return d.pop_back();
        T front()                   return d.front();
        T back()                    return d.back();
        bool full()                 return d.full();
        bool empty()                return d.empty();
        size_t size()               return d.size();
};
#endif