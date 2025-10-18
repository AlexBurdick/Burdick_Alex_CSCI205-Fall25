//#include "OpenHashTable.hpp"
//#include "Contact.h"
#include <iostream>
#include <string>
#include <cmath>
#include "OpenHashTable.hpp"

using namespace std;

int main() {
    int cap = 11;
    OpenHashTable<int> ht(cap);
    string str = "test";
    ht.put("test", 0);
    ht.print();
}