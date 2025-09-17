#ifndef QUEUE_H
#define QUEUE_H
/*********************************************************************
 * @file  Queue.h
 * 
 * @brief Implementation of the template Queue.
 *********************************************************************/

template <typename T>
class Queue
{
private:
    T* arr; // Pointer to array of queue elements
    int capacity; // Maximum number of elements in the queue
    int front; // Index of the front element
    int rear; // Index of the rear element
    int count; // Current number of elements in the queue
public:
    Queue(int size = 10); // Constructor
    ~Queue(); // DestructorQ

    void enqueue(T item); // Add an item to the queue
    T dequeue(); // Remove and return the front item from the queue
    T peek() const; // Return the front item without removing it

    int size() const; // Return the current size of the queue
    bool isEmpty() const; // Check if the queue is empty
    bool isFull() const; // Check if the queue is full
};
#endif // QUEUE_H