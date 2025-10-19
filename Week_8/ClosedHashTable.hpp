/*
Closed Hash Table: A key is ALWAYS stored in the bucket it is hashed to. 
Collisions are dealt with using separate data structures (e.g. linked lists) in each bucket.
The best structure to use here is a self-balancing binary search tree (e.g. AVL tree, red-black tree) ... but we will use a linked list for simplicity.
And because we have not studied trees yet.

In this assignment, you will implement a closed hash table using a linked list to handle collisions.
You will implement the hash table using a fixed size array instead of a vector.
This will allow you to focus on the details of resizing.

Here is an example of a closed hash table with 10 slots (0-9).
Assume the hash function is hash(key) = (length of key) % 10
Assume the load factor threshold is 0.7 (i.e. if load factor > 0.7, resize the table)
Assume we insert the following key-value pairs in order
	0:
	1: ①
	2: ②②②②②
	3:
	4: ④④④
	5:
	6:
	7: ⑦⑦
	8:
	9: ⑨ 
*/

#ifndef CLOSED_HASH_TABLE_HPP
#define CLOSED_HASH_TABLE_HPP

#include <iostream>
#include <string>
#include "LinkedList.hpp"
#include "HashFunctions.cpp"

template<typename V>
class ClosedHashTable {
	private:
		// Each element in the hash table is a list of HashNodes (linked list)
		// Each HashNode contains a key-value pair
		// The key is a string, and the value is of type V

		// Things to think about:
			// Why do we need to store the key in the HashNode?
			// Why do we not need to track nodes as deleted?
			// What happens when we resize the table? Why is this necessary?
			// What is a good load factor threshold? Why?
		
		struct HashNode {
			std::string key;
			V value;
			HashNode(const std::string& k, const V& v) : key(k), value(v){}
			// overload the == operator so we can easily compare HashNodes
			// This is for linked list comparisons. Why do we need this?
			bool operator==(const HashNode& rhs) {return key == rhs.key;}
			// overload the << operator so we can easily print HashNodes
			friend std::ostream& operator<<(std::ostream& os, const HashNode& node) {
				os << node.key << ": " << node.value;
				return os;
			}
		};

		// The open hash tables are collections of lists of HashNodes
		LinkedList<HashNode>* table;	// dynamically allocated array of LinkedLists
		int _size;						// number of key-value pairs in the hash table
		int capacity;					// number of slots in the hash table

		// helper function to compute hash value
		int hash(const std::string& key) {
			// TO DO
			// You will be experimenting here with varous hashing approaches
			// You will be asked to report on your findings
		}

		// helper function to determine load factor
		double loadFactor() {
			// TO DO
			// You will be experimenting here with varous load factors
			// You will be asked to report on your findings
		}

		// helper function to determine if we should resize
		bool should_resize() {
			// TO DO
		}

		void resize() {
			// TO DO
			// resize capacity to 50% larger, then find next prime number
			// rehash and put all key-value pairs. Why is this necessary?
			// clean up memory from old table
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
			// TO DO
		}

	public:
		ClosedHashTable(int capacity) : 
					_size(0), 
					capacity(capacity)		{/*TO DO*/}	// constructor
		~ClosedHashTable() 					{/*TO DO*/}	// destructor

		void put(std::string& key, V& value){/*TO DO*/}	// insert key-value pair
		V get(std::string& key) 			{/*TO DO*/}	// get value associated with key
		bool remove(std::string& key)		{/*TO DO*/}	// remove key-value pair from hash table
		bool contains(std::string& key)		{/*TO DO*/}	// check if key is in the hash table
		void operator[](std::string& key)	{/*TO DO*/}	// overload the [] operator to access elements in hash table
		
		int size()	{return _size;}			// return the number of key-value pairs in the hash table
		bool empty(){return _size == 0;}		// check if the hash table is empty

		// print the contents of the hash table
		// In order to use this your LinkedList class must have a print() and size() function
		void print() const {
			for (int i = 0; i < capacity; ++i) {
				std::cout << "table[" << i << "]: ";
				if (table[i].size() == 0) std::cout << "EMPTY" << std::endl; // is slot empty?
				else table[i].print();		// you'll need to implement the print() function for LinkedList
			}
		}
};

#endif