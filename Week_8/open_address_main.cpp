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
    QuadHashMap<int> qhm(10); 
    string testStrings[] = {
        "a", "b", "c", "d", "e",
        "apple", "banana", "cherry", "date", "elderberry",
        "strawberry", "watermelon", "pineapple", "blueberry", "raspberry",
        "cat", "car", "cart", "caterpillar", "category",
        "dog", "door", "dorm", "dragon", "dragonfruit",
        "aaa", "bbb", "ccc", "ddd", "eee",
    };
    int numStrings = sizeof(testStrings) / sizeof(testStrings[0]); // from LeChat 10/18/2025
    char testChars[] = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
        'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
        'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3'
    };

    cout << "\nTesting put -\n";
    for (int i = 0; i < numStrings; i++) {
        qhm.put(testStrings[i], testChars[i]); // Insert each string with a dummy value
    }
    qhm.print();

    // Test contains and get
    cout << "\nTesting contains and get -\n";
    for (int i = 0; i < numStrings; i++) {
        if ( qhm.contains(testStrings[i]) ) {
            cout << "Found " << testStrings[i] << " = " << qhm.get(testStrings[i]);
        }
    }
    
    cout << "\nTesting remove -\n";
    for (int i = 0; i < numStrings; i++) {
        if (qhm.remove(testStrings[i])) {
            cout << "Removed: " << testStrings[i] << endl;
        }
    }

    // Test subscript operator
    cout << "\nTesting subscript operator\n";
    try {
        string key = "apple";
        cout << "Value for '" << key << "': " << qhm[key] << endl;
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }

    // Test size and empty
    cout << "\nTest size and empty\n";
    cout << "Size of hash table: " << qhm.size() << endl;
    cout << "Is hash table empty? " << (qhm.empty() ? "Yes" : "No") << endl;
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

    //system("python grapher.py");
}