/* g++ -g -Wall -pedantic -o a.out *.cpp *.hpp *.h
 * valgrind --tool=memcheck --leak-check=full ./a.out
 */

#include <iostream>
#include <string>
#include "ClosedHashTable.hpp"

using namespace std;

int main() {
    // Tests suggested by LeChat, modified by author (10/19/2025)
    ClosedHashTable<float> ht(5);
    string testStrings[] = {"apple", "banana", "cherry", "date", "elderberry", "fig", "grape"};
    float testFloats[] = {37.2614f, 12.8439f, 95.6721f, 44.5005f, 78.3294f, 5.1234f, 66.6667f};
    int numStrings = sizeof(testStrings) / sizeof(testStrings[0]); // from LeChat 10/18/2025

    // Test put
    cout << "Testing put-\n";
    for (int i = 0; i < numStrings; ++i) {
        ht.put(testStrings[i], testFloats[i]);
    }
    cout << "\nHash Table after insertion\n" << endl;
    ht.print();

    // Test get
    cout << "\nTesting get-\n";
    for (int i = 0; i < 7; ++i) {
        try {
            int val = ht.get(testStrings[i]);
            cout << "Key: " << testStrings[i] << " = " << val << endl;
        } catch (const runtime_error& e) {
            cerr << e.what() << endl;
        }
    }

    // Test contains
    cout << "\nTesting contains-\n";
    for (int i = 0; i < numStrings; i++) {
        if ( ht.contains(testStrings[i]) ) {
            cout << "Found " << testStrings[i] << " = " << ht.get(testStrings[i]);
        }
    }

    // Test remove
    cout << "\nTesting remove-\n";
    string keysToRemove[] = {"banana", "date", "kiwi"};
    for (int i = 0; i < 3; i++) {
        bool removed = ht.remove(keysToRemove[i]);
        cout << keysToRemove[i] << " : " << (removed ? "Success" : "Failed") << endl;
    }
    ht.print();

    // Test subscript operator
    cout << "\nTesting subscript operator\n";
    try {
        string key = "apple";
        cout << "Value for '" << key << "': " << ht[key] << endl;
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }

    // Test size and empty
    cout << "\nTest size and empty\n";
    cout << "Size of hash table: " << ht.size() << endl;
    cout << "Is hash table empty? " << (ht.empty() ? "Yes" : "No") << endl;

    return 0;
}