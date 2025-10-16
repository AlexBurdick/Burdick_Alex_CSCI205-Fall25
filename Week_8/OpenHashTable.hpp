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
		// Each element in the hash table is a HashNode
		// Each HashNode contains a key-value pair and a flag to indicate if it is deleted
		// The key is a string, and the value is of type V
		// If a HashNode is deleted, it should be skipped during searching. Why?
		// The key is also stored along with the value in the HashNode. Why?
		struct HashNode {
			// Member variables
			std::string key;
			V value;
			bool deleted;

			// Constructors
			HashNode() : key(""), value(V()), deleted(false) {}
			HashNode(std::string& k, V& v) : key(k), value(v), deleted(false) {}
		};

		// So that you can focus on the details of hash table implementation, we will
		// implement the hash table using a fixed size array instead of a vector
		// this will allow you to focus on the details of resizing
		HashNode* table;	// dynamically allocated array of HashNodes
		int size;			// number of key-value pairs in the hash table
		int capacity;		// number of slots in the hash table

		/**
		 * @brief Helper function to determine load factor (𝜆)
		 * 
		 * @return double 
		 */
		double loadFactor() {
			double 𝜆 = capacity / size;
			return 𝜆 ;
		}

		// helper function to determine if we should resize
		
		bool should_resize() {
			if (loadFactor() > 0.75)  return true;
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
			int newCapacity = capacity * 1.5;
			if ( !(is_prime(newCapacity)) ){
				newCapacity = find_next_prime(newCapacity);
			}

			// Create a new hash map
			OpenHashTable<V> newHashTable = new OpenHashTable<V>;

			// Fill new hash map
			for (int node : this) put(key);

			// clean up memory from old table
			delete oldHashMap;
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

		// helper function to find the next prime number
		int find_next_prime(int n) {
			// TO DO
		}

		// helper function to put key-value pairs into the hash table using linear probing
		void put_with_linear_probe(std::string& key, V& value)	{/* TO DO */}

		// helper function to put key-value pairs into the hash table using quadratic probing
		void put_with_quadratic_probe(std::string& key, V& value){/* TO DO */}

	public:
		// Constructor
		OpenHashTable(int capacity) : size(0), capacity(capacity) {
			
		}
		~OpenHashTable()					{/*TO DO*/}	// destructor

		void put(std::string& key, V& value){/*TO DO*/}	// insert key-value pair into the hash table using a put-helper
		bool remove(std::string& key)		{/*TO DO*/}	// remove key-value pair from the hash table
		V get(std::string& key)				{/*TO DO*/}	// get value associated with key
		bool contains(std::string& key)		{/*TO DO*/}	// check if key is in the hash table
		void operator[](std::string& key)	{/*TO DO*/}	// overload the [] operator to access elements in hash table

		int size()	{return size;}			// return the number of key-value pairs in the hash table
		bool empty(){return size == 0;}		// check if the hash table is empty

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
				stream<<hash.slots[i]<<": "<<hash.data[i]<<endl;
			}
			return stream;
		}

	};

#endif
