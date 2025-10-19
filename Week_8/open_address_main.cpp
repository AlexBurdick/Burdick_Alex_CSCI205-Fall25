/* g++ -g -Wall -pedantic -o a.out *.cpp *.hpp *.h
 * valgrind --tool=memcheck --leak-check=full ./a.out
 */

//#include "Contact.h"
#include <iostream>
#include <string>
#include <cmath>
#include "OpenHashTable.hpp"

using namespace std;

int main() {
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

    for (int i = 0; i < cap; i++) {
        ht.put(testStrings[i], i);
    }
    
    for (int i = 0; i < cap; i++) {
        try {
            cout << "get: " << ht.get(testStrings[i]) << endl;
        } catch (const exception& e) {
            cout << e.what() << endl;
        }
    }
    
    ht.print();
}