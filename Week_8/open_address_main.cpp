/* g++ -g -Wall -pedantic -o a.out *.cpp *.hpp *.h
 * valgrind --tool=memcheck --leak-check=full ./a.out
 */
/*
int find_empty_slot(const std::string& key, int cap) {
    int h = lengthDependent(key, cap);
    int start = h;
    do {
        if (newTable[h].key == "") { // Find an empty slot
            return h;
        }
        h = (h + 1) % cap;
    } while (h != start);
    return -1; // Table is full (should not happen if newCapacity is correct)
} */

//#include "Contact.h"
#include <iostream>
#include <string>
#include <cmath>
#include "OpenHashTable.hpp"
#include "QuadHashMap.hpp"

using namespace std;

// Function prototypes
void testLinearOpen();
void testQuadOpen();

int main() {
    // testLinearOpen();
    testQuadOpen();
}

void testQuadOpen() {
    std::string testStrings[] = {
        "a", "b", "c", "d", "e",
        "apple", "banana", "cherry", "date", "elderberry",
        "strawberry", "watermelon", "pineapple", "blueberry", "raspberry",
        "cat", "car", "cart", "caterpillar", "category",
        "dog", "door", "dorm", "dragon", "dragonfruit",
        "aaa", "bbb", "ccc", "ddd", "eee",
    };
    int numStrings = sizeof(testStrings) / sizeof(testStrings[0]);

    QuadHashMap<int> qhm(10); 
    for (int i = 0; i < numStrings; i++) {
        qhm.put(testStrings[i], i); // Insert each string with a dummy value
    }

    // Print the hash map (optional)
    qhm.print();
}

void testLinearOpen() {
    // Array of strings for testing OpenHashTable
    std::string testStrings[] = {
        "apple", "banana", "cherry", "date", "elderberry",
        "fig", "grape", "honeydew", "kiwi", "lemon",
        "mango", "nectarine", "orange", "papaya", "quince",
        "raspberry", "strawberry", "tangerine", "ugli", "vanilla",
        "watermelon", "ximenia", "yellowfruit", "zucchini", "avocado",
        "blueberry", "cantaloupe", "dragonfruit", "eggfruit", "fruit1",
        "fruit2", "fruit3", "fruit4", "fruit5", "fruit6"
    };
    // Number of test strings
    int cap = sizeof(testStrings) / sizeof(testStrings[0]);
    OpenHashTable<int> ht(cap);

    // Test empty and print
    if (ht.empty())  ht.print();

    // Test put
    for (int i = 0; i < cap; i++) {
        ht.put(testStrings[i], i);
    }
    
    // Test get
    for (int i = 0; i < cap; i++) {
        try {
            cout << "get: " << ht.get(testStrings[i]) << endl;
        } catch (const exception& e) {
            cout << e.what() << endl;
        }
    }

    // Test remove
    for (int i = 0; i < cap; i++) {
        ht.remove(testStrings[i]);
    }

    // Test contains
    for (int i = 0; i < cap; i++) {
        ht.contains(testStrings[i]);
    }

    // Test results
    for (int i = 0; i < cap; i++) {
        try {
            cout << "get: " << ht.get(testStrings[i]) << endl;
        } catch (const exception& e) {
            cout << e.what() << endl;
        }
    }

    ht.print();
    
    // Test subscript operator
    OpenHashTable<char> openHT(3);
    openHT.put("test", 'A');
    openHT.print();
    openHT["test"] = 'B';
    char testVal = openHT["test"];
    openHT.print();
    cout << "testVal:  " << testVal;
}