#include <iostream>;
#include <string>;

using namespace std;

int main() {
    /**
     * Call each function and write the results to text files
     */

    return 0;
}

/**
1. Constant Time – Array Middle Element: Write a C++ function that takes an array of integers 
and returns the middle element. Analyze the time complexity and discuss why it is O(1). Ensure
that the plot aligns with constant time. */
int getMiddleElement(int arr[], int size) {
    if (size % 2 == 0) {
        return arr[(size / 2) - 1]; // Return the lower middle for even-sized arrays
    } else {
        return arr[size / 2]; // Return the middle element for odd-sized arrays
    }
}

/**
2. Linear Time – Array Range: Implement a function to find the range of all elements in an array
of integers using a loop. Analyze its time complexity and discuss why it is O(n). Ensure that the 
plot aligns with linear time. */
int findRange(int arr[], int size) {
    if (size <= 0) return 0; // Handle empty array case

    int min = arr[0];
    int max = arr[0];

    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    return max - min; // Return the range
}

/**
3. Linear Time - Exponential Function: Implement an iterative function to calculate the result of
raising a number to a power (e.g., x^n). Do not use any library exponentiation, use brute force 
iterative multiplication.  Analyze and discuss its time complexity. Ensure that the plot aligns 
with your conclusions. */
int power(int base, int exponent) {
    if (exponent < 0) return 0; // Handle negative exponents if needed
    if (exponent == 0) return 1; // Any number to the power of 0 is 1

    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base; // Multiply base, exponent times
    }
    return result;
}

/**
4. Quadratic Time – Square Matrix Max Element: Write a function to find the maximum 
element in a square matrix (number of rows == number of columns) of integers. The function 
should accept a reference to the matrix and the size N. N will represent both the number oif 
columns and number of rows. Analyze its time complexity, and discuss in detail why it is O(n^2). Ensure that the plot aligns 
with quadratic time. */
int findMaxInMatrix(int** matrix, int N) {
    int maxElement = matrix[0][0]; // Assume the first element is the maximum

    for (int i = 0; i < N; i++) { // Loop through rows
        for (int j = 0; j < N; j++) { // Loop through columns
            if (matrix[i][j] > maxElement) {
                maxElement = matrix[i][j]; // Update max if current element is greater
            }
        }
    }

    return maxElement; // Return the maximum element found
}

/**
5. Linear Time - Factorials: Write an iterative function to calculate the factorials of a number, 
not including 1 and itself. It must be O(n). Analyze its time complexity and discuss why it is 
O(n). Ensure that the plot aligns with linear time. */
int factorial(int n) {
    if (n < 0) return -1; // Factorial is not defined for negative numbers
    if (n == 0 || n == 1) return 1; // Base case: 0! = 1 and 1! = 1

    int result = 1;
    for (int i = 2; i <= n; i++) { // Start from 2 to n
        result *= i; // Multiply result by i
    }
    return result;
}

/**
6. Linear (or Better?) - Prime Numbers: Using the concept of “trial division” write a function 
that implements an iterative solution to determine if any number N is prime. Analyze and 
discuss the time complexity of this approach. Implement the strategy that cuts trial division off 
at the square root of N. Analyze and discuss the time complexity of this approach. Graph both. */
bool isPrime(int N) {
    if (N <= 1) return false; // Numbers less than or equal to 1 are not prime
    if (N <= 3) return true; // 2 and 3 are prime numbers

    if (N % 2 == 0 || N % 3 == 0) return false; // Eliminate multiples of 2 and 3

    for (int i = 5; i * i <= N; i += 6) { // Check for factors from 5 to sqrt(N)
        if (N % i == 0 || N % (i + 2) == 0) {
            return false; // Found a factor, not prime
        }
    }
    return true; // No factors found, it is prime
}

/**
7. Quadratic Time – Array has duplicates?: Write a boolean function that determines if an array
contains any duplicate items. Provide a detailed analysis of the time complexity and discuss 
why it is O(n^2). Ensure that the plot aligns with quadratic time. */
bool hasDuplicates(int arr[], int size) {
    for (int i = 0; i < size; i++) { // Outer loop
        for (int j = i + 1; j < size; j++) { // Inner loop
            if (arr[i] == arr[j]) {
                return true; // Found a duplicate
            }
        }
    }
    return false; // No duplicates found
}