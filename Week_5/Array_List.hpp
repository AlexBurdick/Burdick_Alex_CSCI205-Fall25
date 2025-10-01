/*******************************************************************************
 * @file  main.cpp
 * 
 * @brief This class defines an array implemented as a list, templated to allow 
 * for any type of data to be stored in the list. The array will maintain a 
 * continuous seriers of elements, and each elements contains an item in the 
 * list. The ArrayList class tracks the capacity and size of the list. The list 
 * class contains methods for adding, removing, and finding elements from the 
 * list, and a method for printing the contents of the list.
 ******************************************************************************/

#ifndef LIST_ARRAY_HPP
#define LIST_ARRAY_HPP

#include <iostream>
#include <stdexcept>
#include <stack>

template <class T>
class ArrayList{
	private:
		T* array;		/**< Memory allocation for the list. */
		int size;		/**< Number of elements stored in the list. */
		int capacity;	/**< Initial size of the array. */

		// Helper function to resize the array
		void resize(){
			capacity *= 2; // Double capacity
			T* newArray = new T[capacity];

			// Copy old array into new array
			for( int i = 0; i < size; i++ ){
				newArray[i] = array[i];
			}

			delete[] array; // Deallocate memory
			array = newArray; // Point to new array
		}

	public:
		// CONSTUCTORS
		/**
		 * @brief Construct a new List object with the capacity pass in.
		 * 
		 * @param cap capacity of the memory set aside, defaults to 100.
		 */
		ArrayList(int cap = 100) : capacity{cap}, size{0} {
			array = new T[capacity];
		}


		~ArrayList(){
			delete[] array; // deallocate membory
		}


		// MEMBER FUNCTIONS
		/**
		 * @brief insert item at beginning of list
		 * 
		 * @param item 
		 */
		void insert(T item){
			if ( length() == capacity ) resize(); // Resize if full

			for( int i = size-1; i >= 0; i-- ){ // iterage backwards
				array[i+1] = array[i];
			}

			array[0] = item;
			++size;
		}

		/**
		 * @brief insert item at position
		 * 
		 * @param item 
		 * @param pos
		 */
		void insert(T item, int pos){
			if( pos > size ) throw std::out_of_range("Position is out of range");
			if( length() == capacity ) resize(); // Resize if full

			for( int i = size-1; i >= pos; i-- ){ // iterage backwards
				array[i+1] = array[i];
			}

			array[pos] = item;
			++size;
		}

		/**
		 * @brief Add an item to the end of the array.
		 * 
		 * @param item 
		 */
		void add(T item){
			if( length() == capacity ) resize(); // Resize if full
			array[size] = item;
			++size;
		}

		/**
		 * @brief return the item at the head of the list without removing it
		 * 
		 * @return T 
		 */
		T peek(){
			if ( empty() ) throw std::out_of_range("Position is out of range");
			return array[0];
		}

		/**
		 * @brief get item at position
		 * 
		 * @param pos 
		 * @return T 
		 */
		T get(int pos){
			if( pos > size || empty() ) throw std::out_of_range("Position is out of range");
			return array[pos];
		}

		/**
		 * @brief Find the first position of an element in the array.
		 * 
		 * @param item 
		 * @return int index of item
		 */
		int find(T item){
			if( empty() ) throw std::out_of_range("Position is out of range");
			for( int i = 0; i < size; i++ ){
				if ( array[i] == item ) return i;
			}
			return -1;
		}


		/**
		 * @brief remove and return item at specified position
		 * 
		 * @param pos
		 * @return T 
		 */
		T erase(int pos){
			if( pos < 0 || pos >= size || empty() ) throw std::out_of_range("Position is out of range");

			T temp = array[pos];
			for (int i = pos; i < size - 1; i++) {
            	array[i] = array[i + 1]; // Shift elements left
        	}
			--size;

			return temp;
		}

		/**
		 * @brief Remove all instances of an item from the list.
		 * 
		 * @param item 
		 */
		void remove(T item){
			if( empty() ) throw std::out_of_range("Position is out of range");
			
			for (int i = 0; i < size; i++){
            	if( array[i] == item ){
					erase(i); // Use existing erase function
				}
        	}
		}

		/**
		 * @brief print list in neat format
		 * 
		 */
		void print(){
			std::cout << "Array_List: [ ";
			for (int i = 0; i < size; i++) {
				std::cout << array[i] << "(" << i << ") ";
        	}
			std::cout << "]" << std::endl;
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

		/**
		 * @brief Return the instances of “item” in the list.
		 * 
		 * @param item to look for 
		 * @return int number of items
		 */
		int count(T item){
			if( empty() ) throw std::out_of_range("Position is out of range");
			
			int count = 0; // Counter of items to be returned
			for( int i = 0; i < size; i++ ){
				if ( array[i] == item ) count++;
			}

			return count;
		}

		/**
		 * @brief Remove all duplicates from the list.
		 * 
		 * This approach is O(n²) in time complexity, which is fine for small 
		 * lists but inefficient for large ones.
		 */
		void remove_duplicates(){
			if( empty() ) throw std::out_of_range("Position is out of range");

			for( int i = 0; i < size; i++ ){
				for( int j = i+1; j < size; ){ // Start from i+1 to avoid self comparison
					if ( array[i] == array[j] ){
						erase(j);
						--size;
					} else {
						j++; // Only increment if duplicate was not found
					}
				}
			}
		}

		/**
		 * @brief Reverse the list.
		 * 
		 */
		void reverse(){
			if( empty() ) throw std::out_of_range("Position is out of range");

			std::stack<int> listStack; /**< Stack to use LIFO behavior to store data */
			
			// Get all of the data in the list
			for( int i = 0; i < size; i++ ){
				listStack.push(array[i]);
			}
			
			// Write all of the data back to the list in the reverse order
			for( int i = 0; i < size; i++ ){
				array[i] = listStack.top();
				listStack.pop();
			}
		}

		/**
		 * @brief Appends parameter “list” to “this” list.
		 * 
		 * @param list Reference to a list to be added to this list.
		 * @param s Size of the list being added.
		 */
		void append(ArrayList<T>& list, int s){
			while( (size + s) > capacity ) resize(); // Increase size to accomodate new list
			for( int i = 0; i < s; i++ ){ // Iterate through passed in list
				this->add(list.get(i)); // Append item from passed in list
			}
		}
};
#endif
