//#include "OpenHashTable.hpp"
//#include "Contact.h"
#include <iostream>
#include <string>
#include <cmath>
#include "OpenHashTable.hpp"

using namespace std;

int main() {
    int cap = 5;
    string arr[5] = {"string1", "string2", "string3", "string4", "string5"};

    OpenHashTable<int> ht(cap);
    for (int i = 0; i < cap; i++) {
        ht.put("test", i);
    }
    ht.print();
}