#include <string>
#include <cstdlib> // For integers
#include <cmath>   // For floats

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
int midSquare(const double key, int cap) {

    // Convert to int
    int num = static_cast<long>(std::round(key));

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
 * @param int
 * @return int
 */
int digitAnalysis(const int key, int cap) {
    
    // Convert number to string
    std::string str = std::to_string(key);

    // Remove the first character
    if (str.length() >= 2)  str.erase(0, 1);
    // Remove the last character
    if (str.length() >= 2)  str.erase(str.length() - 1, 1);
    // Swap first and last characters
    if (str.length() >= 2)  std::swap(str.front(), str.back());

    // Convert string back to number
    int hashVal = std::stoi(str) % cap;
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