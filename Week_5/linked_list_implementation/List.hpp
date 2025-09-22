/*
	This class defines a singly linked list. It is templated to allow for
	any type of data to be stored in the list. The list is implemented as
	a linked list of nodes. Each node contains a "payload" of templated type
	and a pointer to the next node in the list. The list class tracks the
	head of the list and the size of the list. The list class contains
	methods for adding and removing nodes from the list. The list class
	also contains a method for printing the contents of the list.
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
using namespace std;

// The struct describing the node. This could also be a class
template <class T>
struct Node{
	T item;				// The node's "payload"
	Node<T>* next;		// pointer to the "next" node
};

template <class T>
class List{
	private:
		Node<T>* head;	// pointer to beginning of list
		int size;		// number of elements

	public:
		/**
		 * @brief Construct a new List object
		 * 
		 */
		List();

		/**
		 * @brief Construct a new List object
		 * 
		 * @param size 
		 */
		List(size_t size);

		/**
		 * @brief Construct a new List object
		 * 
		 * @param payload 
		 * @param size 
		 */
		List(T* payload, size_t size);

		/**
		 * @brief Destroy the List object
		 * 
		 */
		~List();

		/**
		 * @brief insert item at beginning of list
		 * 
		 * @param item 
		 */
		void insert(T item);

		/**
		 * @brief insert item at position
		 * 
		 * @param item 
		 * @param position 
		 */
		void insert(T item, int position);

		/**
		 * @brief append item to end of list
		 * 
		 * @param item 
		 */
		void append(T item);

		/**
		 * @brief get item at position
		 * 
		 * @param position 
		 * @return T 
		 */
		T get(int position);

		/**
		 * @brief remove and return item at specified position
		 * 
		 * @param position 
		 * @return T 
		 */
		T remove(int position);

		/**
		 * @brief remove all instances of item from list
		 * 
		 * @param item 
		 */
		void remove(T item);
		
		/**
		 * @brief print list in neat format
		 * 
		 */
		void print();
		
		/**
		 * @brief return length of list
		 * 
		 * @return int 
		 */
		int length();
};
#endif
