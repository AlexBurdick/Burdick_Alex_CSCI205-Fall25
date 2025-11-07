/*
Closed Hash Table: A key is ALWAYS stored in the bucket it is hashed to. 
Collisions are dealt with using separate data structures (e.g. linked lists) in each bucket.

In this assignment, you will implement a closed hash table using a linked list to handle collisions.
You will implement the hash table using a fixed size array instead of a vector.

Assume the hash function is midSquare(key, capacity)
Assume the load factor threshold is 0.7 (i.e. if load factor > 0.7, resize the table)
*/

#ifndef CLOSED_HASH_TABLE_HPP
#define CLOSED_HASH_TABLE_HPP

#include <iostream>
#include <string>
#include <vector>
#include "LinkedList.hpp"
#include "HashFunctions.hpp"

template<typename V>
class ClosedHashTable {
	private:
		struct HashNode {
			std::string key;
			V value;

			// Constructors
			HashNode() : key(""), value(V()) {}
			HashNode(const std::string& k, const V& v) : key(k), value(v) {}
			
			// overload the == operator so we can easily compare HashNode. Why do we need this?
			// This allows us to compare the keys easily by just doing node == node
			bool operator==(const HashNode& rhs) {
				return key == rhs.key;
			}
			
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
		int hash(const std::string& key, int cap) {
			return digitAnalysis(key, cap);
		}

		// helper function to determine load factor
		double loadFactor() {
			return static_cast<double>(_size) / capacity;
		}

		// helper function to determine if we should resize
		bool should_resize() {
			return loadFactor() > 0.7;
		}

		// resize the hash table when it exceeds the load factor
		void resize() {
			int newCapacity = find_next_prime(static_cast<int>(capacity * 1.5));
			LinkedList<HashNode>* newTable = new LinkedList<HashNode>[newCapacity];

			for (int i = 0; i < capacity; ++i) {
				Node<HashNode>* current = table[i].getHead();
				while (current != nullptr) {
					int h = hash(current->payload.key, newCapacity);
					newTable[h].add(current->payload);
					current = current->next;
				}
			}

			// Clean up memory from old table
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
			while (!is_prime(n)) n += 1;
            return n;
		}

	public:
		// constructor
		ClosedHashTable(int capacity) : _size(0), capacity(capacity) {
			table = new LinkedList<HashNode>[capacity];
		}
		
		~ClosedHashTable() {
			delete[] table;
		}

		// insert key-value pair
		void put(const std::string& key, const V& value, int* tester = nullptr) {
			if (should_resize()) resize();
			int h = hash(key, capacity);

			// Always count the first probe attempt
    		if (tester != nullptr) (*tester)++;

			// Check if key already exists
			Node<HashNode>* current = table[h].getHead();
			while (current != nullptr) {
				if (tester != nullptr) (*tester)++;
				if (current->payload.key == key) {
					current->payload.value = value;
					return;
				}
				current = current->next;
			}

			// Key not found, add new node
			HashNode newNode(key, value);
			table[h].add(newNode);
			_size++;
		}
		
		// get value associated with key
		V get(const std::string& key, int* tester = nullptr) {
			// Always count the first probe attempt
    		if (tester != nullptr) (*tester)++;
			
			int h = hash(key, capacity);
			Node<HashNode>* current = table[h].getHead();

			while (current != nullptr) {
				if (tester != nullptr) (*tester)++;
				if (current->payload.key == key) {
					return current->payload.value;
				}
				current = current->next;
			}
			throw std::runtime_error("Key not found");
		}

		// remove key-value pair from hash table
		bool remove(const std::string& key, int* tester = nullptr) {
			// Always count the first probe attempt
    		if (tester != nullptr) (*tester)++;
			
			int h = hash(key, capacity);
			Node<HashNode>* current = table[h].getHead();

			int pos = 0;
			while (current != nullptr) {
				if (tester != nullptr) (*tester)++;
				if (current->payload.key == key) {
					table[h].erase(pos);
					_size--;
					return true;
				}
				current = current->next;
				pos++;
			}
			return false;
		}
		
		// check if key is in the hash table
		bool contains(const std::string& key) {
			int h = hash(key, capacity);
			Node<HashNode>* current = table[h].getHead();
			while (current != nullptr) {
				if (current->payload.key == key) return true;
				current = current->next;
			}
			return false;
		}

		// overload the [] operator to access elements in hash table (from LeChat, 10/19/2025)
		V& operator[](const std::string& key) {
			int h = hash(key, capacity);
			Node<HashNode>* current = table[h].getHead();
			while (current != nullptr) {
				if (current->payload.key == key) {
					return current->payload.value;
				}
				current = current->next;
			}
			throw std::runtime_error("Key not found");
		}

		int getCap() {return capacity;}   // return the capacity (for looping through list)
		int size()	 {return _size;}	  // return the number of key-value pairs in the hash table
		bool empty() {return _size == 0;} // check if the hash table is empty

		/**
		 * @brief Updated print function from DeepSeek (11/06/2025)
		 * 
		 */
		void print() const {
			for (int i = 0; i < capacity; ++i) {
				std::cout << "table[" << i << "]: ";
				if (table[i].empty()) {
					std::cout << "EMPTY" << std::endl;
				} else {
					Node<HashNode>* current = table[i].getHead();
					// Print all nodes in this bucket
					while (current != nullptr) {
						std::cout << current->payload.key << " = " << current->payload.value;
						current = current->next;
						if (current != nullptr)
							std::cout << " -> "; // separator for multiple entries
					}
					std::cout << std::endl;
				}
			}
		}

		/**
		 * @brief Get the keys, values in this hash table. This is for iterating
		 * through key, value pairs without knowing the keys.
		 * From DeepSeek (11/07/2025)
		 * 
		 * @return std::vector<HashNode> 
		 */
		std::vector<HashNode> getEntries() const {
			std::vector<HashNode> entries;
			for (int i = 0; i < capacity; ++i) {
				Node<HashNode>* current = table[i].getHead();
				while (current != nullptr) {
					entries.push_back(current->payload);
					current = current->next;
				}
			}
			return entries;
		}
};

#endif