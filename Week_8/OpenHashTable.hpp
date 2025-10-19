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
#include <stdexcept>
#include "HashFunctions.hpp"

template<typename V>
class OpenHashTable {
	private:
		// The key is a string, and the value is of type V
		struct HashNode {
			// Member variables
			std::string key;
			V value;
			bool deleted;

			// Constructors
			HashNode() : key(""), value(V()), deleted(false) {}
			HashNode(const std::string& k, const V& v) : key(k), value(v), deleted(false) {}
		};

		double _size;	 // number of key-value pairs in the hash table
		double capacity; // number of slots in the hash table
		HashNode* table; // Default value is nullptr to determine existence

		// helper function to determine load factor (𝜆)
		double loadFactor() {
			double lf = _size / capacity;
			return lf ;
		}

		// helper function to determine if we should resize
		bool should_resize() {
			double lf = loadFactor();
			if (lf > 0.5) return true;
			else return false;
		}

		// helper function to resize the table. This will rehash and put all 
		// key-value pairs. Why is this necessary?
		// - We need to do this because when the capacity changes the hash values for 
		// - all keys will also change.
		void resize() {
			int newCapacity = find_next_prime(capacity * 2);
			HashNode* newTable = new HashNode[newCapacity];
			for (int i = 0; i < capacity; i++) {
				if (table[i].key != "" && !table[i].deleted) {
					int h = lengthDependent(table[i].key, newCapacity);
					while (newTable[h].key != "") { // Handle collisions
						h = (h + 1) % newCapacity;
					}
					newTable[h] = table[i]; // Insert key into the empty slot
				}
			}
			// clean up memory from old table
			delete[] table;
			table = newTable;
			capacity = newCapacity;
		}
		
		// helper function to determine if a number is prime
		bool is_prime(int n) {
			if (n <= 1) return false;
			if (n <= 3) return true;
			if (n % 2 == 0 || n % 3 == 0) return false;
			for (int i = 5; i * i <= n; i = i + 6)
				if (n % i == 0 || n % (i + 2) == 0)
					return false;
			return true;
		}

		// helper function to find the next prime number
		int find_next_prime(int n) {
			while (!is_prime(n))  n += 1;
			return n;
		}
		
		
		// helper function to put key-value pairs into the hash table using
		// linear probing. The resize is called before this in the put function.
		int linear_probe(const std::string& key) {
			int h = lengthDependent(key, capacity);
			int counter = 0;

			// Loop until next availalbe slot is found
			while ( table[h].key != "" && table[h].key != key ) {
				h = (h + 1) % static_cast<int>(capacity);
				counter++;
				if (counter >= capacity) return -1;	// This should not be encountered 
			}								  		// for put or resize, but needed  
			return h;								// for remove, get, and contains.
		}

	public:
		/**
		 * @brief Construct a new Open Hash Table object
		 * 
		 * @param capacity 
		 */
		OpenHashTable(int capacity) : _size(0), capacity(capacity) {
			table = new HashNode[capacity];
		}

		/**
		 * @brief Destroy the Open Hash Table object
		 * 
		 */
		~OpenHashTable()  { delete[] table; }

		/**
		 * @brief Insert key-value pair into the hash table using linear probing. 
		 * Uses the linear_probe helper function for deal deal with collisions.
		 * 
		 * @param key
		 * @param value
		 */
		void put(const std::string& key, const V& value) {
			if (should_resize()) resize();
			int h = linear_probe(key);

			// Table is full and key was not found (something went wrong with sizing)
			if ( h == -1) {
				throw std::runtime_error("Resize: sizing error");
			// Key was not found (empty slot)
			} else if ( table[h].key == "" ) {
				table[h].key = key;
				table[h].value = value;
				_size++;
			// Key was found
			} else { 
				if ( table[h].deleted == true ) {
					table[h].deleted = false;
					_size++;
				}
				table[h].value = value;
			}
		}

		/**
		 * @brief Remove key-value pair from the hash table
		 * 
		 * @param key to look for
		 * @return bool whether or not key was found
		 */
		bool remove(const std::string& key) {
			int h = linear_probe(key);

			// If key was not found
			if (h == -1 || table[h].key == "") {
				return false;
			// Key found (regarless of deleted)
			} else {
				table[h].deleted = true;
				_size--;
				return true;
			}
		}

		/**
		 * @brief get value associated with key
		 * 
		 * @param key 
		 * @return V 
		 */
		V get(const std::string& key) {
			int h = linear_probe(key);

			// If key was not found
			if ( h == -1 || table[h].key == "" ) {
				throw std::runtime_error("Key '" + key + "' not found in hash table");
			// Key found but deleted
			} else if ( table[h].deleted == true ) {
				throw std::runtime_error("Key '" + key + "' was deleted from hash table");
			// Key found
			} else {
				return table[h].value;
			}
		}

		/**
		 * @brief Check if key is in the hash table.
		 * 
		 * @param key 
		 * @return true 
		 * @return false 
		 */
		bool contains(const std::string& key) {
			int h = linear_probe(key);

			// If key was not found (or was deleted)
			if ( h == -1 || table[h].deleted || table[h].key == "" ) {
				return false;
			// Key found
			} else {
				return true;
			}  
		}

		/**
		 * @brief overload the [] operator to access elements in hash table 
		 * (from LeChat, 10/18/2025)
		 * 
		 * @param key 
		 * @return V& needs to be returnes as a referenced so it can be accessed
		 */
		V& operator[](const std::string& key) {
			if (should_resize()) resize();
			int h = linear_probe(key);
			if (h == -1) {
				throw std::runtime_error("Subscript: sizing error");
			// Key not found: insert a default-constructed value
			} else if (table[h].key == "") {
				table[h].key = key;
				table[h].value = V(); // Default-constructed value
				table[h].deleted = false;
				_size++;
			// Key was deleted: reinsert with a default-constructed value
			} else if (table[h].deleted) {
				table[h].deleted = false;
				table[h].value = V(); // Default-constructed value
				_size++;
			}
			// Return a reference to the value
			return table[h].value;
		}

		/**
		 * @brief Return the number of key-value pairs in the hash table
		 * 
		 * @return int 
		 */
		double size() const { return _size; }

		/**
		 * @brief Check if the hash table is empty
		 * 
		 * @return true 
		 * @return false 
		 */
		bool empty() { return _size == 0; }

		/**
		 * @brief Print out all the key-value pairs in the hash table
		 * 
		 */
		void print() {
			if (empty()) {
				std::cout << "Empty" << std::endl;
			} else {
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
		}
	};

#endif