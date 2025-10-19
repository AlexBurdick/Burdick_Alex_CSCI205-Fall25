#ifndef QUAD_HASH_MAP_HPP
#define QUAD_HASH_MAP_HPP
#include <string>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include "HashFunctions.cpp"

template<typename V>
class QuadHashMap {
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
        int _size;      // number of key-value pairs in the hash table
        int capacity;   // number of slots in the hash table
        HashNode* table; // Default value is nullptr to determine existence

        // Helper function to determine load factor (λ)
        double loadFactor() {
            return static_cast<double>(_size) / capacity;
        }

        // Helper function to determine if we should resize
        bool should_resize() {
            return loadFactor() > 0.5;
        }

        // Helper function to resize the table
        void resize() {
            int newCapacity = find_next_prime(capacity * 2);
            HashNode* newTable = new HashNode[newCapacity];
            for (int i = 0; i < capacity; i++) {
                if (table[i].key != "" && !table[i].deleted) {
                    int h = lengthDependent(table[i].key, newCapacity);
                    int j = 1;
                    // Quadratic probing for insertion
                    while (newTable[h].key != "") {
                        h = (h + j * j) % newCapacity;
                        j++;
                    }
                    newTable[h] = table[i]; // Insert key into the empty slot
                }
            }
            // Clean up memory from old table
            delete[] table;
            table = newTable;
            capacity = newCapacity;
        }

        // Helper function to determine if a number is prime
        bool is_prime(int n) {
            if (n <= 1) return false;
            if (n <= 3) return true;
            if (n % 2 == 0 || n % 3 == 0) return false;
            for (int i = 5; i * i <= n; i = i + 6)
                if (n % i == 0 || n % (i + 2) == 0)
                    return false;
            return true;
        }

        // Helper function to find the next prime number
        int find_next_prime(int n) {
            while (!is_prime(n)) n += 1;
            return n;
        }

        // Helper function to find a slot using quadratic probing
        int quadratic_probe(const std::string& key) {
            int h = lengthDependent(key, capacity);
            int j = 1;
            int counter = 0;
            // Loop until next available slot is found
            while (table[h].key != "" && table[h].key != key) {
                h = (h + j * j) % capacity;
                j++;
                counter++;
                if (counter >= capacity) return -1; // Table is full
            }
            return h;
        }

    public:
        /**
         * @brief Construct a new Quad Hash Map object
         *
         * @param capacity
         */
        QuadHashMap(int capacity) : _size(0), capacity(capacity) {
            table = new HashNode[capacity];
        }

        /**
         * @brief Destroy the Quad Hash Map object
         */
        ~QuadHashMap() { delete[] table; }

        /**
         * @brief Insert key-value pair into the hash table using quadratic probing.
         *
         * @param key
         * @param value
         */
        void put(const std::string& key, const V& value) {
            if (should_resize()) resize();
            int h = quadratic_probe(key);
            if (h == -1) {
                throw std::runtime_error("Resize: sizing error");
            } else if (table[h].key == "") {
                // Key not found: insert new key-value pair
                table[h].key = key;
                table[h].value = value;
                table[h].deleted = false;
                _size++;
            } else {
                // Key found: update value
                if (table[h].deleted) {
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
            int h = quadratic_probe(key);
            if (h == -1 || table[h].key == "") {
                return false; // Key not found
            } else {
                table[h].deleted = true;
                _size--;
                return true;
            }
        }

        /**
         * @brief Get value associated with key
         *
         * @param key
         * @return V
         */
        V get(const std::string& key) {
            int h = quadratic_probe(key);
            if (h == -1 || table[h].key == "") {
                throw std::runtime_error("Key '" + key + "' not found in hash table");
            } else if (table[h].deleted) {
                throw std::runtime_error("Key '" + key + "' was deleted from hash table");
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
            int h = quadratic_probe(key);
            return !(h == -1 || table[h].deleted || table[h].key == "");
        }

        /**
         * @brief Overload the [] operator to provide map[key] behavior.
         *
         * @param key
         * @return V& Reference to the value associated with the key.
         */
        V& operator[](const std::string& key) {
            if (should_resize()) resize();
            int h = quadratic_probe(key);
            if (h == -1) {
                throw std::runtime_error("Subscript: sizing error");
            } else if (table[h].key == "") {
                // Key not found: insert a default-constructed value
                table[h].key = key;
                table[h].value = V(); // Default-constructed value
                table[h].deleted = false;
                _size++;
            } else if (table[h].deleted) {
                // Key was deleted: reinsert with a default-constructed value
                table[h].deleted = false;
                table[h].value = V(); // Default-constructed value
                _size++;
            }
            return table[h].value;
        }

        /**
         * @brief Return the number of key-value pairs in the hash table
         *
         * @return int
         */
        int size() const { return _size; }

        /**
         * @brief Check if the hash table is empty
         *
         * @return true
         * @return false
         */
        bool empty() { return _size == 0; }

        /**
         * @brief Print out all the key-value pairs in the hash table
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
