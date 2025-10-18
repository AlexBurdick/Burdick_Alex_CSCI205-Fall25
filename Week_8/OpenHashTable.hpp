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

		int size {0};	  // number of key-value pairs in the hash table
		int capacity {61}; // number of slots in the hash table
		HashNode* table; // Default value is nullptr to determine existence

		/**
		 * @brief Helper function to determine load factor (𝜆)
		 * 
		 * @return double 
		 */
		double loadFactor() {
			double 𝜆 = size / capacity;
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

			// Fill new hash map
			for (int i = 0; i < capacity; i++) {
				if (table[i] && !table[i].deleted) {
            		int h = lengthDependent(table[i].key, newCapacity);
            		newTable[h]->put(table[i].key, table[i].value);
       			}
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
			return (h + 1) % capacity;
		}
		
		// helper function to put key-value pairs into the hash table using linear probing
		int linear_probe(std::string& key) {
			int h = lengthDependent(key, capacity);
			int count = 1;
			
			// Loop until next availalbe slot is found
			while (table[h].key != "" && table[h].key != key ) {
				h = rehash(h);
			}
				
			// Empty slot
			if (table[h].key == "") return -1;
			else return h;
		}

		// helper function to put key-value pairs into the hash table using quadratic probing
		void put_with_quadratic_probe(std::string& key, V& value){/* TO DO */}

	public:
		// Constructor
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
			if (should_resize()) resize();
			int h = linear_probe(key);

			// If key was not found
			if (h == -1) {
				table[h] = HashNode(key, value);
			} else { // Key was found
				table[h].deleted = false;
				table[h].value = value;
			}
		}

		/**
		 * @brief Remove key-value pair from the hash table
		 * 
		 * @param key to look for
		 * @return bool whether or not key was found
		 */
		bool remove(std::string& key) {
			int h = linear_probe(key);

			// If key was not found
			if (h == -1) {
				return false;
			} else { // Key was found
				table[h].deleted = true;
				return true;
			}
		}

		/**
		 * @brief get value associated with key
		 * 
		 * @param key 
		 * @return V 
		 */
		V get(std::string& key) {
			int h = linear_probe(key);

			if (h == -1) { // If key was not found
				throw std::runtime_error("Key '" + key + "' not found in hash table");
			// Key found
			} else if (table[h].deleted == true ) {
				throw std::runtime_error("Key '" + key + "' not found in hash table");
			} else {
				return table[h].value;
			}
		}

		// check if key is in the hash table
		bool contains(std::string& key)	{
			int h = linear_probe(key);

			if (h == -1) { // If key was not found
				return false;
			} else if (table[h].deleted == true ) { // Been deleted
				return false;
			} else { // Key found
				return true;
			}
		}

		// overload the [] operator to access elements in hash table
		void operator[](std::string& key)	{/*TO DO*/}

		/**
		 * @brief Return the number of key-value pairs in the hash table
		 * 
		 * @return int 
		 */
		int size() {
			return size;
		}

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

	};

#endif
