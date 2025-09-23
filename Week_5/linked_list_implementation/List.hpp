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
		List(){
			head = null;
			size = 0;
			
		}

		/**
		 * @brief Construct a new List object
		 * 
		 * @param size 
		 */
		List(size_t size){
			head = null;
			this->size = size;
		}

		/**
		 * @brief Construct a new List object
		 * 
		 * @param payload 
		 * @param size 
		 */
		List(T* payload, size_t size){
			head = new Node<T>(); // instantiate new node to contain item
			head->item = payload;
			this->size = size;
		}

		/**
		 * @brief Destroy the List object
		 * 
		 */
		~List(){
			cout << "List destructor called" << endl; 	// just for visual clues
			Node<T> *current = head;					// start deleting at head
			while (current != NULL){					// iterate until we find a next NULL reference
				cout << "Node deleted" << endl;			// just for visual clues
				Node<T> *next = current->next;			// advance "current" pointer to "next"
				delete current;							// deallocate the memory pointed to by "current"
				current = next;							// set current to "next"
			}
			head = NULL;								// set head to NULL	
		}

		/**
		 * @brief insert item at beginning of list
		 * 
		 * @param item 
		 */
		void insert(T item){
			Node<T> *temp = new Node<T>();
			temp->item = data;	// assign the new node its "payload". Templated for flexibility

			// check to see if this is the first item added
			// need to configure the "head" reference if so
			if(this->empty()) head = temp;	// not first item added
			else{
				temp->next	= head;			// push old "head" down the list
				head		= temp;			// new item then becomes the head
			}
			++size;							// increase the size
		}

		/**
		 * @brief insert item at position
		 * 
		 * @param item 
		 * @param position 
		 */
		void insert(T item, int pos){
			Node<T> *temp = new Node<T>();
			temp->item = data;

			// Check to see if the position is out of range
			if( pos > size ) {
				throw std::out_of_range("Position (" + size + ") is out of range (" + size + ")");
			}
			else if(this->empty()) head = temp;	// first item added
			else{
				temp->next = head;			// push old "head" down the list
				for( int i = 0; i < pos; i++ ){

				}
				temp->next	= ;			// push old "head" down the list
				head		= temp;			// new item then becomes the head
			}
			++size;							// increase the size
		}

		/**
		 * @brief append item to end of list
		 * 
		 * @param item 
		 */
		void append(T item);

		/**
		 * @brief return the item at the head of the list without removing it
		 * 
		 * @return T 
		 */
		T peek(){
			return head->item;
		}

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
		void print(){
			Node<T> *current = head;		// start at the head
			int count = 1;					// enumerate just for kicks
			while(current != NULL){			// loop until current is null
				cout << "<Node " << count++ << ": " << current->item << "> ==> ";
				current = current->next;	// step the reference down the list
			}
			cout << "NULL" << endl;
		}
		
		/**
		 * @brief return length of list
		 * 
		 * @return int 
		 */
		int length() const{
			return size;
		}

		/**
		 * @brief return true if the list is empty
		 * 
		 * @return true 
		 * @return false 
		 */
		bool empty(){
			return count == 0;
		}
};
#endif
