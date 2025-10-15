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
int division(int input) {
    int hashValue = (abs(input) % 552283);
    return hashValue;
}

/**
 * @brief Midsquare Method: Multiply the key by itself and select an appropriate 
 * number of bits or digits from the middle of the square. The same positions must be 
 * used for all products
 * 
 */
int midSquare(std::string input) {
    int hashValue = 1;

    // Convert string to int value
    for (char c : input) {
        int asciiValue = c;
        hashValue *= pow(asciiValue, 2);
    }

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

3. Digit Analysis: This approach forms an address by selecting and shifting digits or bits 
from the original key
a. Example:
i. Key → 7546123
ii. Select digits 3 to 6 and reverse the order
iii. Hash →2164
b. For a given key space the same positions and techniques should be used 
consistently
c. Ideally some analysis is performed before hand to determine which digits have the
most uniform distribution across the key space

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
