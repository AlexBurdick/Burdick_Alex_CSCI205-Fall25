#ifndef LIST_ARRAY_HPP
#define LIST_ARRAY_HPP

template <class T>
class Array_List{
	private:
		T* array;				// memory allocation for list elements
		size_t size 	{0};	// variable to hold the size
		size_t capacity {100};

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
		}

	public:
		/**
		 * @brief Construct a new List object withe default values.
		 * 
		 */
		List() { array = new T[capacity]; }

		/**
		 * @brief Construct a new List object with the capacity pass in.
		 * 
		 * @param cap capacity
		 */
		List(size_t cap) : capacity{cap} {
			array = new T[capacity];
		}


		~List(){
			delete[] array; // deallocate membory
		}

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
		 * @param pos
		 */
		void insert(T item, int pos);

		/**
		 * @brief append item to end of list
		 * 
		 * @param item 
		 */
		void append(T item);

		/**
		 * @brief get item at position
		 * 
		 * @param pos 
		 * @return T 
		 */
		T get(int pos);

		/**
		 * @brief find item at position
		 * 
		 * @param target 
		 * @return int index of target
		 */
		int find(T target){
			for( int i = 0; int < size; int++ ){
				current = current->next;
				++index;
			}
			return -1;
		}


		/**
		 * @brief remove and return item at specified position
		 * 
		 * @param pos
		 * @return T 
		 */
		T remove(int pos){
			if( lenght() == 0 || pos > length() ){
				throw std::out_of_range("Position is out of range.");
			}

			if( length() == 1 ){

			}
			--capacity; // Decrease capacity
			for( int i = pos; i < capacity; i++ ){ // Copies from beyond new capacity
				array[i] = array[i+1]
			}
		}

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
		int length(){
			return size;
		}
};
#endif
