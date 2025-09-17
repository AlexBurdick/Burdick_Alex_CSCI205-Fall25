/*********************************************************************
 * @file  Stack.hpp
 * 
 * @brief Implementation of the class Stack.
 *********************************************************************/

#ifndef STACK_H
#define STACK_H

template <typename T> // added

class Stack
{
private:
    T* arr; // changed to T*
    int capacity;
    int top;
};
#endif // STACK_H