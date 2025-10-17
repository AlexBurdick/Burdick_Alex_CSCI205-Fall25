/*
Open Hash Table: A key is NOT ALWAYS stored in the bucket it is hashed to.
Collisions are dealt with by probing for another empty buckets within the hash table array itself.
The simplest probing method is linear probing, where we simply check the next bucket in the array.
If that bucket is occupied, we check the next one, and so on, until we find an empty bucket.
Another probing method is quadratic probing, where we check buckets at increasing intervals (e.g. 1, 4, 9, 16, ...).
This can help to reduce clustering of key collisions.
*/

#ifndef OPEN_HASH_TABLE_HPP
#define OPEN_HASH_TABLE_HPP

#include <string>
#include <iomanip>
#include <iostream>
#include "HashFunctions.cpp"

template<typename V>
class OpenHashTable{
	private:
		// The key is a string, and the value is of type V
		struct HashNode {
			// Member variables
			std::string key;
			V value;
			bool deleted;

			// Constructors
			HashNode() : key(""), value(V()), deleted(false) {}
			HashNode(std::string& k, V& v) : key(k), value(v), deleted(false) {}
		};

		int size;	  // number of key-value pairs in the hash table
		int capacity; // number of slots in the hash table
		HashNode* table[capacity] = {nullptr}; // Default value is nullptr to determine existence

		/**
		 * @brief Helper function to determine load factor (𝜆)
		 * 
		 * @return double 
		 */
		int loadFactor() {
			int 𝜆 = size / capacity;
			return 𝜆 ;
		}

		// helper function to determine if we should resize
		
		bool should_resize() {
			if (loadFactor() > 0.5)  return true;
			else  return false;
		}

		/**
		 * @brief Helper function to resize the table. This will rehash and put all 
		 * key-value pairs. Why is this necessary? We need to do this because when 
		 * the capacity changes the hash values for all keys will also change.
		 * 
		 */
		void resize() {
			// Get a new capacity and make sure it's prime
			int newCapacity = find_next_prime(capacity * 2);

			// Create a new hash map
			HashNode* newTable = new HashNode[newCapacity];

			for (i = 0; i < capacity; i++) {
				if table[i] = 
			}

			// Fill new hash map
			for (i = 0; i < capacity; i++) {
				int h = lengthDependent(table[i].key, newCapacity);
            	newTable[h] = table[i];
			}

			// clean up memory from old table
			delete[] table;
			table = newTable;
    		capacity = newCapacity;
		}

		/**
		 * @brief Helper function to determine if a number is prime
		 * 
		 * @param n 
		 * @return true if the n is prime
		 * @return false if n is not prime
		 */
		bool is_prime(int n) {
			if (n <= 1) return false;
			if (n <= 3) return true;
			if (n % 2 == 0 || n % 3 == 0) return false;
			for (int i = 5; i * i <= n; i = i + 6)
				if (n % i == 0 || n % (i + 2) == 0)
					return false;
			return true;
		}

		/**
		 * @brief helper function to find the next prime number
		 * 
		 * @param n 
		 * @return int 
		 */
		int find_next_prime(int n) {
			while (!is_prime(n))  n += 1;
			return n;
		}

		/**
		 * @brief Helper function to put key-value pairs into the hash table using 
		 * linear probing, from Runestone
		 * 
		 * @param key 
		 * @param value 
		 */
		int rehash(int h) {
			int newHash = (h + 1) % capacity;
			return;
		}
		
		// helper function to put key-value pairs into the hash table using linear probing
		void put_with_linear_probe(std::string& key, V& value) {
			int h = lengthDependent(key, capacity);
			int count = 0;
			
			if (table[h].deleted) {
				table[h].deleted = false;
				table[h].key = key;
				table[h].value = value;
			}
			else if (!(table[h])) {
				table[h] = new HashNode(key, value);
			}
			else {
				int counter = 0;
				int next = rehash(h);

				// Loop until next availalbe slot is found
				while ( table[next] && table[next] != key ) {
					next = rehash(next);
					counter++;
					if (counter > size) { // resize if needed
						resize();
						next = rehash(next);
					}
				}
				
				// Empty slot
				if ( !(table[next]) ) { 
					table[next] = new HashNode(key, value);
					size++;
				// Key is found, deleted or not
				} else {
					table[next].deleted = false;
					table[next].key 	= key;
					table[next].value 	= value;
				}
			}
		}

		// helper function to put key-value pairs into the hash table using quadratic probing
		void put_with_quadratic_probe(std::string& key, V& value){/* TO DO */}

	public:
		// Constructor
		OpenHashTable() = default;
	
		OpenHashTable(int capacity) : size(0), capacity(capacity) {
			table = new HashNode[capacity];
		}

		// Destructor
		~OpenHashTable() {
			// Delete all HashNodes
			for (int i = 0; i < capacity; i++)  delete table[i];
			delete table;
		}

		/**
		 * @brief Insert key-value pair into the hash table using linear probing, 
		 * from Runestone.
		 * 
		 * @param key
		 * @param value
		 */
		void put(std::string& key, V& value) {
			put_with_linear_probe(key, V& value);
			//void put_with_quadratic_probe(std::string& key, V& value){/* TO DO */}
		}

		/**
		 * @brief Remove key-value pair from the hash table
		 * 
		 * @param key to look for
		 * @return bool whether or not key was found
		 */
		bool remove(std::string& key) {
			int h = lengthDependent(key, capacity);
			
			if (table[h].key == key) {
				table[h].deleted = true;
				return true;
			} else {
				int counter = 0;
				int next = rehash(h);

				// Loop until next availalbe slot is found
				while ( table[next] && table[next] != key ) {
					next = rehash(next);
					counter++;
					if (counter > size) { // resize if needed
						resize();
						next = rehash(next);
					}
				}

				if (!table[next]) { // Empty slot
					return false;
				} else { // Key found
					table[next].deleted = true;
					return true;
				}
			}
		}

		/**
		 * @brief get value associated with key
		 * 
		 * @param key 
		 * @return V 
		 */
		V get(std::string& key) {
			int h = lengthDependent(key, capacity);

			if ( table[h].key == key && !table[h].deleted ) {
				return table[h].value;
			} else {
				int counter = 0;
				int next = rehash(h);

				// Loop until next availalbe slot is found
				while ( table[next] &&
					  ( table[next] != key || table[next].deleted) )
				{
					next = rehash(next);
					counter++;
					if (counter == size - 1)  return; // Key not found
				}

				if (!table[next]) { // Empty slot
					return;
				} else { // Key found
					return table[next].value;
				}
			}
		}

		// check if key is in the hash table
		bool contains(std::string& key)		{/*TO DO*/}

		// overload the [] operator to access elements in hash table
		void operator[](std::string& key)	{/*TO DO*/}

		int size()	 return size;	   // return the number of key-value pairs in the hash table
		bool empty() return size == 0; // check if the hash table is empty

		// print out all the key-value pairs in the hash table
		// use this function to help you debug your code
		void print() {
			for (int i = 0; i < capacity; i++) {
				std::cout << "table[ ";
				if (table[i].deleted)
					std::cout << i << " ]\t= DELETED" << std::endl; 
				else if (table[i].key != "")
					std::cout << table[i].key << " ]\t= " << table[i].value << std::endl;
				else 
				 	std::cout << i << " ]\t= EMPTY" << std::endl;
			}
		}
		
		/**
		 * @brief Overloaded output operator
		 * 
		 * @param stream 
		 * @param hash 
		 * @return ostream& 
		 */
		ostream& operator<<(ostream& stream, HashTable& hash) {
			for (int i=0; i<hash.size; i++) {
				stream << hash.table[i] << ": "<< hash.table[i] << endl;
			}
			return stream;
		}

	};

#endif
