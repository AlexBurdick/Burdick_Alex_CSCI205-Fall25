//#include "OpenHashTable.hpp"
//#include "Contact.h"
#include <iostream>
#include <string>
#include <cmath>
#include "OpenHashTable.hpp"

using namespace std;

int main() {
    int cap = 11;
    string str = "test";

    OpenHashTable<int> ht(cap);
    for (int i = 0; i < cap; i++) {
        ht.put("test", i);
    }
    ht.print();
}