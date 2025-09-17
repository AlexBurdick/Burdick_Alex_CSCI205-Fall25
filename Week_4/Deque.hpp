/*********************************************************************
 * @file  Deque.hpp
 * 
 * @brief Implementation of the class Deque.
 *********************************************************************/

#ifndef DEQUE_H
#define DEQUE_H

template <typename T> // Template class definition, interchange T with any type
class Deque{
	
	private:
		// Private member variables to manage insertion and removal points
		size_t size;	 // number of items in the deque, acts as counter needs to be incremented and decremented
		size_t capacity; // size of the array
		size_t front;	 // index of the front of the deque
		size_t back;	 // index of the back of the deque
		T* array;		 // array to store items (pointer to type T, to be determined at run time)

		// Helper function to resize the array
		void resize(){
			capacity *= 2; // Double capacity
			T* newArray = new T[capacity];
			// Copy old array into new array
			for (size_t i = 0; i < size; i++)
			{
				newArray[i] = array[front + i];
			}
			front = 0; // Reset front
			back = size - 1; // Reset back
			delete[] array; // Deallocate memory
			array = newArray; // Point to new array

			// ANSWER: What is the big O notation for this function? How did you come to that conclusion?
			// - O(n), n is the number of elements in the array. It would be O(1) if we didn't copy the old array.
		}

	public:
		/**
		 * @brief Construct a new Deque object
		 * 
		 */
		Deque(){
			capacity= 100;
			size 	= 0;
			front 	= 0;
			back 	= capacity - 1;
			array	= new T[capacity]; // create dynamic memory for array of template type T
		}

		/**
		 * @brief Construct a new Deque object with a given capacity
		 * 
		 * @param cap The capacity of the deque
		 */
		Deque(size_t cap){
			if (cap == 0) cap = 1; // Data validation, cannot be 0
			capacity= cap;
			size 	= 0;
			front 	= 0;
			back 	= capacity - 1;
			array	= new T[capacity];
		}

		/**
		 * @brief construct a new Deque object from an existing array
		 * 
		 * @param arr the array to copy items from
		 * @param size the number of items in the array
		 */
		Deque(T* arr, size_t size){
			// ensure the array is not null. Throw an invalid argument exception if it is
			if (arr == nullptr) throw invalid_argument("Array cannot be null");
			if (size == 0) throw invalid_argument("Size cannot be zero");
			
			// set the capacity to double the size of the array
			capacity = size * 2;
			
			// set the size to the size of the array
			this->size = size; // nees this pointer as size is a passed in variable
			
			// copy the items from the given array to the deque's array
			array = new T[capacity];
			for (size_t i = 0; i < size; i++){
				array[i] = arr[i];
			}
			
			// set the front and back indices appropriately
			front = 0;
			back = size - 1;
		}

		/**
		 * @brief Destroy the Deque object and de-allocate dynamic memory
		 * 
		 */
		~Deque(){
			delete[] arr;
		}				

		/**
		 * @brief Inserts an item at the front of the deque
		 * 
		 * @param item item to be added to the front of the deque
		 */
		void push_front(const T item){
			// If the array is full, call resize() to double the size of the array
			if full resize;

			// note: no need to check if you are at the end of the array
			// modulus division will take care of that for you
			


		}

		/**
		 * @brief Inserts an item at the back of the deque
		 * 
		 * @param item item to be added to the back of the deque
		 */
		void push_back(const T item){
			// ===============================
			// || TO DO: Handle wrap around ||
			// ===============================

			// note: no need to check if you are at the end of the array
			// modulus division will take care of that for you
			// If the array is full, call resize() to double the size of the array
		}

		/**
		 * @brief Removes the item at the front of the deque and returns it
		 * 
		 * @return T the item removed from the front of the deque
		 */
		T pop_front(){
			// ===============================
			// || TO DO: Handle wrap around ||
			// ===============================

			// If the deque is empty, throw an out_of_range exception
			
		}

		/**
		 * @brief Removes the item at the back of the deque and returns it
		 * 
		 * @return T the item removed from the back of the deque
		 */
		T pop_back(){
			// ===============================
			// || TO DO: Handle wrap around ||
			// ===============================

			// If the deque is empty, throw an out_of_range exceptio
		}

		/**
		 * @brief returns but does not remove the item at the front of the deque
		 * 
		 * @return T the item at the front of the deque
		 */
		T front(){  return array[front]  }

		/**
		 * @brief Returns but does not remove the item at the back of the deque
		 * 
		 * @return T the item at the back of the deque
		 */
		T back(){  return array[back]  }

		/**
		 * @brief Returns whether or not the deque is full
		 * 
		 * @return true, if the deque is full
		 * @return false, if the deque is not full
		 */
		bool full(){  return size == capacity;  }

		/**
		 * @brief Returns whether or not the deque is empty
		 * 
		 * @return true, if the deque is empty
		 * @return false, if the deque is not empty
		 */
		bool empty(){  return size == 0  }

		/**
		 * @brief Returns the number of items in the deque
		 * 
		 * @return size_t, the number of items in the deque
		 */
		size_t size(){  return size  }	
};

#endif
