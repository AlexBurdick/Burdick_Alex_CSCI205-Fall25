/*********************************************************************
 * @file  Deque.hpp
 * 
 * @brief Implementation of the class Deque.
 *********************************************************************/

#ifndef DEQUE_H
#define DEQUE_H

// Questions: 
// - what makes it abstract? how is is different from java again?
// - what does 'new' do?

template <typename T> // Template class definition, interchange T with any type
class Deque{
	
	private:
		// Private member variables to manage insertion and removal points
		size_t size_var;  /**< Number of elements in the array, acts as a counter. */
		size_t capacity;  /**< Total size of the array allocated. */
		size_t front_var; /**< Index of the front of the deque. */
		size_t back_var;  /**< Index of the back of the deque */
		T* array; /**< Array to store items (pointer to type T, to be determined at run time). */

		// Helper function to resize the array
		void resize(){
			int newCapacity = capacity * 2; // Double capacity
			T* newArray = new T[newCapacity];

			// Copy old array into new array
			for( size_t i = 0; i < size_var; i++ ){
				newArray[i] = array[ (back_var + i + capacity) % capacity ];
			}

			capacity = newCapacity;
			front_var = size_var - 1; // Reset front
			back_var = 0; // Reset back
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
			size_var = 0;
			capacity = 100;
			front_var = capacity - 1;
			back_var = 0;
			array = new T[capacity]; // create dynamic memory for array of template type T
		}

		/**
		 * @brief Construct a new Deque object with a given capacity
		 * 
		 * @param cap The capacity of the deque
		 */
		Deque(size_t cap){
			if (cap < 1) cap = 1; // Data validation, cannot be 0
			capacity = cap;
			size_var = 0;
			front_var = capacity - 1;
			back_var = 0;
			array = new T[capacity];
		}

		/**
		 * @brief construct a new Deque object from an existing array
		 * 
		 * @param arr the array to copy items from
		 * @param size_var the number of items in the array
		 */
		Deque(T* arr, size_t size){
			// ensure the array is not null. Throw an invalid argument exception if it is
			if (arr == nullptr) throw invalid_argument("Array cannot be null");
			if (size == 0) throw invalid_argument("Size cannot be zero");
			
			// set the capacity to double the size of the array
			capacity = size * 2;
			
			// copy the items from the given array to the deque's array
			array = new T[capacity];
			for (size_t i = 0; i < size; i++){
				array[i] = arr[i];
			}
			
			// set the front and back indices appropriately
			front_var = size - 1;
			back_var = 0;
			size_var = 0;
		}

		/**
		 * @brief Destroy the Deque object and de-allocate dynamic memory
		 * 
		 */
		~Deque(){
			delete[] array;
		}				

		/**
		 * @brief Inserts an item at the front of the deque
		 * 
		 * @param item item to be added to the front of the deque
		 */
		void push_front(const T& item){
			// If the array is full, call resize() to double the size of the array
			if (full()){
				resize();
			}
			front_var = (front_var + 1 + capacity) % capacity;
			array[front_var] = item;
			size_var++;
		}

		/**
		 * @brief Inserts an item at the back of the deque
		 * 
		 * @param item item to be added to the back of the deque
		 */
		void push_back(const T& item){
			// If the array is full, call resize() to double the size of the array
			if (full()){
				resize();
			}
			back_var = (back_var - 1 + capacity) % capacity;
			array[back_var] = item;
			size_var++;
		}

		/**
		 * @brief Removes the item at the front of the deque and returns it
		 * 
		 * @return T the item removed from the front of the deque
		 */
		T pop_front(){
			// If the deque is empty, throw an out_of_range exception
			if ( empty() ){
				throw out_of_range("Deque is empty");
			}
			T item = array[front_var];
			front_var = (front_var - 1 + capacity) % capacity;
			size_var--;
			return item;
		}

		/**
		 * @brief Removes the item at the back of the deque and returns it
		 * 
		 * @return T the item removed from the back of the deque
		 */
		T pop_back(){
			// If the deque is empty, throw an out_of_range exceptio
			if (empty()){
				throw out_of_range("Deque is empty");
			}
			T item = array[back_var];
			back_var = (back_var + 1 + capacity) % capacity;
			size_var--;
			return item;
		}

		/**
		 * @brief returns but does not remove the item at the front of the deque
		 * 
		 * @return T the item at the front of the deque
		 */
		T front(){
			return array[front_var];
		}

		/**
		 * @brief Returns but does not remove the item at the back of the deque
		 * 
		 * @return T the item at the back of the deque
		 */
		T back(){
			return array[back_var];
		}

		/**
		 * @brief Returns whether or not the deque is full
		 * 
		 * @return true, if the deque is full
		 * @return false, if the deque is not full
		 */
		bool full(){
			return (size_var == capacity);
		}

		/**
		 * @brief Returns whether or not the deque is empty
		 * 
		 * @return true, if the deque is empty
		 * @return false, if the deque is not empty
		 */
		bool empty(){
			return (size_var == 0);
		}

		/**
		 * @brief Returns the number of items in the deque
		 * 
		 * @return size_t, the number of items in the deque
		 */
		size_t size(){
			return size_var;
		}

		// Can be moved and used to view the contents of the array within the size
		void print(){
			cout << "Print from back:" << "\n";
			for( int i = 0; i < size_var ; i++ ){
				int j = (back_var + i + capacity) % capacity;
				cout << "Value = " << array[j] << " [" << j << "]" << "\n";
			}
			cout << "Size = " << size_var << "\n" << endl;
		}
};

#endif
