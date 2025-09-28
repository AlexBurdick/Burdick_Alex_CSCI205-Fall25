/*******************************************************************************
 * @file  main.cpp
 * 
 * @brief This class defines a singly linked list, templated to allow for any 
 * type of data to be stored in the list. It list is implemented as a linked 
 * list of nodes. Each node contains a "payload" of templated type and a pointer 
 * to the next node in the list. The LinkedList class tracks the head and size 
 * of the list. The LinkedList class contains methods for adding, removing, and 
 * finding nodes from the list, and a method for printing the contents of the 
 * list.
 ******************************************************************************/

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>
#include <stdexcept>
#include <stack>
#include <string>

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
		int size	  {0};		 /**< Counter for the size of the list. */

		// Helper function to find a node at a position
		Node<T>* getNode(int pos){
			Node<T>* current = head;
				for( int i = 0; i < pos; i++ ){
					current = current->next;
				}
			return current;
		}

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
		LinkedList(T payload){
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
			if( pos > size || pos < 0 ) throw std::out_of_range("Position is out of range");

			Node<T>* newNode = new Node<T>(item);
			if (pos == 0) { // Insert at the head
        		newNode->next = head;
        		head = newNode;
			} else {
				Node<T>* current = getNode(pos-1);
				newNode->next = current->next;
				current->next = newNode;
			}
			++size;	// increase the size
		}

		/**
		 * @brief append item to end of list
		 * 
		 * @param item 
		 */
		void add(T item){
			Node<T>* newNode = new Node<T>(item); // Create new node

			if( head == nullptr ){ // Deal with head
				head = newNode;
			} else {
				Node<T>* current = getNode(size-1);
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
			if ( this->empty() ) throw std::out_of_range("Position is out of range");
			return head->payload;
		}

		/**
		 * @brief get item at position
		 * 
		 * @param position 
		 * @return T 
		 */
		T get(int pos){
			if ( this->empty() || pos < 0 || pos > size ) throw std::out_of_range("Position is out of range");
			Node<T>* current = getNode(pos);
			return current->payload;
		}

		/**
		 * @brief Find an item's first position.
		 * 
		 * @param target item to find 
		 * @return int index of the target
		 */
		int find(T target){
			int index = 0;
			Node<T>* current = head;
			while( current != nullptr ){
				if( current->payload == target ) return index;
				current = current->next;
				++index;
			}
			return -1;
		}

		/**
		 * @brief remove and return item at specified position
		 * 
		 * @param pos index to remove
		 * @return T 
		 */
		T erase(int pos){
			if ( pos >= size || pos < 0 || this->empty() ) throw std::out_of_range("Position is out of range");
			
			T item; /**< Holder for value to be returned */
			Node<T>* toDelete = head; /**< Start at the head */
			if (pos == 0){ 				// Deal with head
				item = head->payload;	// Get the value to return
				head = toDelete->next;	// Set head before deleting it
				delete toDelete;		// Delete previous head
				--size;					// Decrease size
				return item;			// Return value contained at pos
			}

			// Set the node at the correct position, and it's previous node
			Node<T>* previous = getNode(pos-1);
			toDelete = previous->next; // This will be node[pos]
			previous->next = toDelete->next; // Set next pointer of node before deleted node
			
			// Retrieve data
			item = toDelete->payload; // Save value of item that is being erased
			delete toDelete; // Deallocate memory
			--size; // Decrement size
			return item;
		}

		/**
		 * @brief Remove all instances of item from LinkedList.
		 * 
		 * @param target 
		 */
		void remove(T target){
			if( this->empty() ) throw std::out_of_range("Position is out of range");
			
			Node<T>* current = head; /**< Start at the head */
			while (head->payload == target){
				current = head->next;		// Make "next" node the new "head"
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
		void print(){
			Node<T>* current = head;		// start at the head
			int count = 0;					// enumerate just for kicks
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
		const int length(){
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

		/**
		 * @brief Return the instances of “item” in the list.
		 * 
		 * @param item to look for 
		 * @return int number of items
		 */
		int count(const T item){
			if( empty() ) throw std::out_of_range("Position is out of range");
			
			int count = 0; // Counter of items to be returned
			Node<T>* current = head; // Start at the head
			while( current != nullptr ){
				if ( current->payload == item ) count++;
				current = current->next;
			}

			return count;
		}

		/**
		 * @brief Remove all duplicates from the list.
		 * 
		 */
		void remove_duplicates(){
			if( empty() ) throw std::out_of_range("Position is out of range");

			Node<T>* current = head; /**< Node object to act as a placeholder, staring at the head */

			while( current->next != nullptr ){
				Node<T>* runner = current; /**< Holds the node to be compared to the rest of the list. */

				while( runner->next != nullptr ){
				
					if ( current->payload == runner->next->payload ){
						Node<T>* temp = runner->next; // Temp = next node
						runner->next = temp->next;	// Remove the duplicate
						delete temp;				// Deallocate memory
						--size;						// Decrement size
					} else {
						runner = runner->next; // Only advance if no duplicate was found
					}
				}
				current = current->next; // Move to next Node
			}
		}

		/**
		 * @brief Reverse the list.
		 * 
		 */
		void reverse(){
			if( empty() ) throw std::out_of_range("Position is out of range");

			std::stack<int> listStack; /**< Stack to use LIFO behavior to store data */
			Node<T>* current = head; /**< Node object to act as a placeholder, staring at the head */
			
			// Get all of the data in the list
			while( current != nullptr ){
				listStack.push(current->payload); // Store items in the stack in revers order
				current = current->next;
			}

			// Write all of the data back to the list in the reverse order
			current = head;
			while( current != nullptr ){
				current->payload = listStack.top();
				current = current->next;
				listStack.pop();
			}
		}

		/**
		 * @brief Appends parameter “list” to “this” list.
		 * 
		 * @param list Reference to a list to be added to this list.
		 */
		void append(const LinkedList<T>& otherList){
			Node<T>* otherCurrent = otherList.head;
			while (otherCurrent != nullptr) {
				this->add( T(otherCurrent->payload) ); // Use existing add method
				otherCurrent = otherCurrent->next;
			}
		}
};
#endif