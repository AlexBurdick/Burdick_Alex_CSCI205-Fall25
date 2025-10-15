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
long division(const std::string input) {
    
    // Convert string to int value
    long strVal = 1; /*<< Holds the value of the accumulated ascii values */
    for (char c : input) {
        int asciiValue = c;
        strVal += pow(asciiValue, 2); // Make the number big
    }

    // abs() isn't necesary for string inputs, but could be for numbers
    strVal = (abs(strVal) % 552283);
    return strVal;
}

/**
 * @brief Midsquare Method: Multiply the key by itself and select an appropriate 
 * number of bits or digits from the middle of the square. The same positions must be 
 * used for all products
 * 
 * @param double that is converted to int
 * @return long
 */
int midSquare(const double input) {

    // Convert to int
    int num = static_cast<long>(std::round(input));

    // Get number of digits in hashValue (from LeChat, 10/15/2025)
    int numDigits = static_cast<int>(std::log10(num)) + 1;

    // Return if hashValue is 3 digits of less
    if (numDigits <= 3) return num;

    // Divisor (from LeChat, 10/15/2025)
    int divisor = pow(10, (numDigits - 3) / 2 + 1);

    // Get middle three digits (from LeChat, 10/15/2025)
    int middleThree = (num / (divisor / 10)) % 1000;

    return middleThree;
}

/**
 * @brief Digit Analysis: This approach forms an address by selecting and shifting 
 * digits or bits from the original key
 * 
 * @param int 
 */
int digitAnalysis(const int input) {
    
    // Convert number to string
    std::string str = std::to_string(input);

    // Remove the first character
    if (str.length() >= 2)   str.erase(0, 1);
    // Remove the last character
    if (str.length() >= 2)   str.erase(str.length() - 1, 1);
    // Swap first and last characters
    if (str.length() >= 2) {
        std::swap(str.front(), str.back());
    }

    // Convert string back to number
    return std::stoi(str);
}


4. Length Dependence: The length of the key along with some predetermined portion of 
the key is used to form a table address directly or often an intermediary key which is 
further hashed by the division method to form the table address.
a. One string approach that has performed well sums the binary representation of the
first and last characters, added to the length of the key, shifted left 4 bits. In 
decimal parlance this is akin to multiplying the value by 16
b. STUDENT becomes 
i. int(‘S’) + int(‘T’) + (key.length() << 4)
ii. 83 + 84 + (7 << 4) or 83 + 84 + (7 x 16) 
iii. This yields 279 as an intermediate key
iv. Apply the division method with a large-ish prime divisor: 279 % 61   →35
