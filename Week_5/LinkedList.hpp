/*******************************************************************************
 * @file  main.cpp
 * 
 * @brief This class defines a singly linked list, templated to allow for any 
 * type of data to be stored in the list. It list is implemented as a linked 
 * list of nodes. Each node contains a "payload" of templated type and a pointer 
 * to the next node in the list. The List class tracks the head and size of the 
 * list. The list class contains methods for adding and removing nodes from the 
 * list, and a method for printing the contents of the list.
 ******************************************************************************/

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>
#include <stdexcept>

// The struct describing the node. This could also be a class
template <class T>
struct Node{
	T payload;
	Node<T>* next {nullptr};

	/**
	 * @brief Construct a new Node object with default values
	 * 
	 */
	Node() = default;
	
	/**
	 * @brief Construct a new Node object with payload as input.
	 * 
	 */
	Node(T item) : payload{item} {}
};

template <class T>
class LinkedList{
	private:
		Node<T>* head {nullptr}; /**< Pointer to a new node to be the start of the list. */
		int 	 size {0};		 /**< Counter for the size of the list. */

	public:
		/**
		 * @brief Construct a new List object with default values.
		 * 
		 */
		LinkedList() = default;

		/**
		 * @brief Construct a new List object with a payload
		 * 
		 * @param payload 
		 */
		LinkedList(T* payload){
			head = new Node<T>(); // instantiate new node to contain item
			head->payload = payload;
		}

		/**
		 * @brief Destroy the List object
		 * 
		 */
		~LinkedList(){
			while (head != nullptr){		// iterate until we find a next NULL reference
				Node<T>* next = head->next;	// advance "current" pointer to "next"
				delete head;				// deallocate the memory pointed to by "current"
				head = next;				// set current to "next"
			}
			head = nullptr; // Extra cleanup, is this necesary?
		}

		/**
		 * @brief insert item at beginning of list
		 * 
		 * @param item 
		 */
		void insert(T item){
			Node<T>* newNode = new Node<T>(item);
			if( this->empty() ) head = newNode; // Deal with first element in the list
			else{
				newNode->next = head;
				head = newNode;
			}
			++size;
		}

		/**
		 * @brief insert item at position
		 * 
		 * @param item 
		 * @param position 
		 */
		void insert(T item, int pos){
			Node<T>* newNode = new Node<T>(item, nullptr);

			if( pos > size || pos < 0 ){ // Check to see if the position is out of range
				throw std::out_of_range("Position is out of range.");
			}
			else if(this->empty()) head = newNode;	// first item added
			else{
				Node<T>* current = head;
				for( int i = 0; i < pos; i++ ){
					Node<T>* temp = current->next;
				}
				newNode->next = current->next;
				current->next = newNode;
			}
			++size;					// increase the size
		}

		/**
		 * @brief append item to end of list
		 * 
		 * @param item 
		 */
		void append(T item){
			Node<T>* newNode = new Node<T>(item); // Create new node

			if( head == nullptr ){ // Deal with head
				head = newNode;
			} else {
				Node<T>* current = head;
				while( current->next != nullptr ){
					current = current->next;
				}
				current->next = newNode; // Append new node
			}
			++size;
		}

		/**
		 * @brief return the item at the head of the list without removing it
		 * 
		 * @return T 
		 */
		T peek(){
			if ( this->empty() ){
				throw std::out_of_range("Position is out of range.");
			}
			return head->payload;
		}

		/**
		 * @brief get item at position
		 * 
		 * @param position 
		 * @return T 
		 */
		T get(int pos){
			if ( this->empty() ){
				throw std::out_of_range("Position is out of range.");
			}

			Node<T>* current = head;
			for (int i = 0; i < pos; i++){
				current = current->next; // When loop stops, this will be node[pos]
			}

			return current->payload;
		}

		/**
		 * @brief remove and return item at specified position
		 * 
		 * @param position 
		 * @return T 
		 */
		void removeAt(int pos){
			// Check to see if the position is out of range
			if ( pos >= size || pos < 0 || this->empty() ){
				throw std::out_of_range("Position is out of range.");
			}
			
			Node<T>* toDelete = head; // Start at the head			
			if (pos == 0){ // Deal with head
				head = toDelete->next;
				delete toDelete;
				--size;
				return;
			}

			Node<T>* previous = nullptr;
			for (int i = 0; i < pos; i++){
				previous = toDelete;
				toDelete = toDelete->next; // When loop stops, this will be node[pos]
			}
			previous->next = toDelete->next; // Set next pointer of node before deleted node
			delete toDelete;
			--size;
		}

		/**
		 * @brief Remove all instances of item from LinkedList.
		 * 
		 * @param item 
		 */
		void remove(T target){
			if( this->empty() ){
				throw std::out_of_range("Position is out of range.");
			}
			
			Node<T>* current = head;	// Start at the head
			while (head->payload == target){
				current = head->next;			// Make "next" node the new "head"
				delete head;				// Delete head node, making next the new head
				head = current;
				--size;						// Decrease size
			}

			while (current != nullptr){ // Starts at next after head, head was already tested
				Node<T>* next =  current->next;
				if ((next != nullptr) && (next->payload == target)){ // If next node matches
					current->next = next->next; // set current to bypass next
					delete next;				// delete next
					--size;						// decrement size
					continue;
				}
				current = current->next; // continue to the next node
			}
		}
		
		/**
		 * @brief Print the list in a neat format.
		 * 
		 */
		void printList(){
			Node<T> *current = head;		// start at the head
			int count = 1;					// enumerate just for kicks
			while(current != nullptr){		// loop until current is null
				std::cout << "<Node " << count++ << ": " << current->payload << "> ==> ";
				current = current->next;	// step the reference down the list
			}
			std::cout << "NULL" << std::endl;
		}
		
		/**
		 * @brief return length of list
		 * 
		 * @return int 
		 */
		int length(){
			return size;
		}

		/**
		 * @brief return true if the list is empty
		 * 
		 * @return true 
		 * @return false 
		 */
		bool empty(){
			return size == 0;
		}
};

#endif