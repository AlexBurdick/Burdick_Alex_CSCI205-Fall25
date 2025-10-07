/*********************************************************************
 * @file  Stack.hpp
 * 
 * @brief Implementation of the class Stack.
 *********************************************************************/

#ifndef STACK_H
#define STACK_H

#include "Deque.hpp"

template <typename T>
class Stack{
    
    private:
        Deque<T> d;

    public:
        // CONSTRUCTORS
        /**
		 * @brief Default constructor.
		 * 
\		 */
        Stack() = default;

        /**
		 * @brief Construct a new Stack object with a given capacity
		 * 
		 * @param cap The capacity of the stack
		 */
        Stack(size_t cap){
            d = Deque<T>(cap);
        }

        /**
		 * @brief Explicity delete copy constructor
		 * 
		 */
        Stack(const Stack&) = delete;

        // MEMBER FUNCTIONS
        void push(const T& item){
            d.push_front(item);
        }

        T pop(){
            return d.pop_front();
        }

        T peek(){
            return d.front();
        }

        bool full(){
            return d.full();
        }

        bool empty(){
            return d.empty();
        }

        size_t size(){
            return d.size();
        }
};
#endif