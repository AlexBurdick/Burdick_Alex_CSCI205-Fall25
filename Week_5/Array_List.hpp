#ifndef LIST_ARRAY_HPP
#define LIST_ARRAY_HPP

template <class T>
class Array_List{
	private:
		T* memory;			// memory allocation for list elements
		size_t size {0};	// variable to hold the size

	public:
		/**
		 * @brief Construct a new List object
		 * 
		 */
		List() = default;

		/**
		 * @brief Construct a new List object
		 * 
		 * @param size 
		 */
		List(size_t num){
			
		}


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
		 * @brief find item at position
		 * 
		 * @param target 
		 * @return int index of target
		 */
		int find(T target){
			for( int i = 0; int < size; int++ ){
				
			}
				current = current->next;
				++index;
			}
			return -1;
		}


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
