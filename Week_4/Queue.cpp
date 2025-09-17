/*********************************************************************
 * @file  Queue.h
 * 
 * @brief Function definitions of the template Queue.
 *********************************************************************/
#include "Queue.h"
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T> // Do I need this line?
Queue<T>::Queue(int size) // Constructor
{
    arr = new T[size]; // Allocate memory for the queue
    capacity = size;
    front = -1;
    rear = capacity - 1;
    count = 0;
}

template <typename T>
Queue<T>::~Queue() // Destructor
{
    delete[] arr; // Free the allocated memory
}

template <typename T>
void Queue<T>::enqueue(T item) // Add an item to the queue
{
    if (isFull())
    {
        throw overflow_error("Queue is full");
    }
    rear = (rear + 1) % capacity; // Circular increment
    arr[rear] = item;
    count++;
    if (front == -1) // If the queue was empty, set front to 0
    {
        front = 0;
    }
}

template <typename T>
T Queue<T>::dequeue() // Remove and return the front item from the queue
{
    if (isEmpty())
    {
        throw underflow_error("Queue is empty");
    }
    T item = arr[front];
    front = (front + 1) % capacity; // Circular increment
    count--;
    if (count == 0) // If the queue is now empty, reset front and rear
    {
        front = -1;
        rear = capacity - 1;
    }
    return item;
}

template <typename T>
T Queue<T>::peek() const // Return the front item without removing it
{
    if (isEmpty())
    {
        throw underflow_error("Queue is empty");
    }
    return arr[front];
}

template <typename T>
int Queue<T>::size() const // Return the current size of the queue
{
    return count;
}

template <typename T>
bool Queue<T>::isEmpty() const // Check if the queue is empty
{
    return (count == 0);
}

template <typename T>
bool Queue<T>::isFull() const // Check if the queue is full
{
    return (count == capacity);
}