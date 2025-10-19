#ifndef HASH_FUCNTIONS_HPP
#define HASH_FUCNTIONS_HPP

#include <string>
#include <cstdlib> // For integers
#include <cmath>   // For floats

/**
 * @brief Converts a string to a number by summing the ASCII values of its characters.
 *
 * @param str The input string to convert.
 * @return int The resulting number (sum of ASCII values).
 */
int stringNum(const std::string& str) {
    int sum = 0;
    for (char c : str)  sum += static_cast<int>(c);
    return sum;
}

/**
 * @brief Division Method: This function performs well at preserving the uniformity 
 * that exists in a key space. Keys that are closely related or clustered are mapped 
 * to unique indices.
 * 
 * @param key
 * @return int
 */
int divisionHash(const int key, int cap) {
    int hashVal = (abs(key) % cap);
    return hashVal;
}

/**
 * @brief Midsquare Method: Multiply the key by itself and select an appropriate 
 * number of bits or digits from the middle of the square. The same positions must be 
 * used for all products
 * 
 * @param double that is converted to int
 * @return long
 */
int midSquare(const std::string& key, int cap) {
    long num = stringNum(key);
    // Get number of digits in hashValue (from LeChat, 10/15/2025)
    int numDigits = static_cast<int>(std::log10(num)) + 1;

    // Return if hashValue is 3 digits of less
    if (numDigits <= 3) return num;

    // Divisor (from LeChat, 10/15/2025)
    int divisor = pow(10, (numDigits - 3) / 2 + 1);

    // Get middle three digits (from LeChat, 10/15/2025)
    int middleThree = (num / (divisor / 10)) % 1000;
    
    int hashVal = middleThree % cap;
    return hashVal;
}

/**
 * @brief Digit Analysis: This approach forms an address by selecting and shifting 
 * digits or bits from the original key
 * 
 * @param key string to be used in the hash
 * @param cap capacity of the hash map
 * @return int hash value
 */
int digitAnalysis(const std::string& key, int cap) {
    std::string localKey = key; // Create a local copy
    // Remove the first character
    if (key.length() >= 2)  localKey.erase(0, 1);
    // Remove the last character
    if (key.length() >= 2)  localKey.erase(localKey.length() - 1, 1);
    // Swap first and last characters
    if (key.length() >= 2)  std::swap(localKey.front(), localKey.back());

    // Convert string back to number
    int hashVal = stringNum(localKey) % cap;
    return hashVal;
}

/**
 * @brief The length of the key along with some predetermined portion of the key is 
 * used to form a table address directly or often an intermediary key which is 
 * further hashed by the division method to form the table address. One string 
 * approach that has performed well sums the binary representation of the first and 
 * last characters, added to the length of the key, shifted left 4 bits. In decimal 
 * parlance this is akin to multiplying the value by 16
 * 
 * @param key 
 * @return int 
 */
int lengthDependent(const std::string key, int cap) {
    // Data validation, if string is not empty
    if ( !(key.empty()) ) {
        // Get the first and last characters
        int num =  int(key.front()) + int(key.back()) + (key.length() << 4);
        int hashVal = divisionHash(num, cap);
        return hashVal;
    } else {
        return 0;
    }
}

#endif