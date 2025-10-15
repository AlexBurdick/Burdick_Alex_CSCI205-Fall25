//#include "OpenHashTable.hpp"
//#include "Contact.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Quiz is ont insert and retrieve, linear search, binary search, hash table
// To make:
// - Open addressing linear probing
// - Open addressing quadratic probing
// - Closed addressing 

int midSquare(int hashValue) {
    // Get number of digits in hashValue (from LeChat, 10/15/2025)
    int numDigits = static_cast<int>(std::log10(hashValue)) + 1;

    // Return if hashValue is 3 digits of less
    if (numDigits <= 3) return hashValue;

    // Devisor (from LeChat, 10/15/2025)
    int divisor = pow(10, (numDigits - 3) / 2 + 1);

    // Get middle three digits (from LeChat, 10/15/2025)
    int middleThree = (hashValue / (divisor / 10)) % 1000;
    
    return middleThree;
}

int main() {
    cout << "1: " << midSquare(1) << "\n";
    cout << "22: " << midSquare(22) << "\n";
    cout << "333: " << midSquare(333) << "\n";
    cout << "4321: " << midSquare(4321) << "\n";
    cout << "51235: " << midSquare(51235) << "\n";
    cout << "612346: " << midSquare(612346) << "\n";
    cout << "7123457: " << midSquare(7123457) << "\n";
    cout << "81234568: " << midSquare(81234568) << "\n";
}