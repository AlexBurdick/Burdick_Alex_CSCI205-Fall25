#include <iostream>
#include <vector>
#include <array>
#include <string>
#include "Deque.hpp"
#include "Stack.hpp"
#include "Array_List.hpp"
#include "Linked_List.hpp"

using namespace std;

int recursive_gcd(int a, int b);
int iterative_gcd(int a, int b);
long fibonacci(const long n);
string iterative_reverse(string s);
string recursive_reverse(string s);
int triangular_number_50(int n = 50);
int sum(ArrayList<int>& array);
int recursive_sum(ArrayList<int>&, int index);

int main(){
    // Fibonacci
    int n;
    cout << "--Testing Fibonacci function--\n";
    cout << "Enter a number: ";
    cin >> n;
    cout << "The " << n << "th Fibonacci number is " << fibonacci(n) << endl;

    // GCD
    int d;
    cout << "\n--Testing GCD Function--\n";
    cout << "Enter the numerator: ";
    cin >> n;
    cout << "Enter the denominator: ";
    cin >> d;
    cout << "The GCD of " << n << "/" << d << " is " << recursive_gcd(n, d) << endl;

    // String reverse
    string s;
    cout << "\n--Testing Iterative String Reverse Function--\n";
    cout << "Enter a string: ";
    cin >> s;
    cout << "Reversed string: " << iterative_reverse(s) << endl;

    cout << "\n--Testing Recursive String Reverse Function--\n";
    cout << "Enter a string: ";
    cin >> s;
    cout << "Reversed string: " << recursive_reverse(s) << endl;

    // Triangular number
    cout << "\n--Testing Recursive Triangular number Function--\n";
    cout << "Triangular number of 50 = " << triangular_number_50() << endl;

    // Array sum
    ArrayList<int> intList = {1, 2, 3, 4}; // list for testing, sum = 10
    cout << "\n--Testing Recursive Array Sum--\n";
    cout << "The sum of the array is " << sum(intList) << endl;
}

/** 1.
 * @brief Simulate recursion by writing an iterative method that reverses a string 
 * using an explicit stack of your design.
 * Time complexity = O(n)
 * Spacial complexity = O(1)
 * 
 * @param s string to be reversed
 * @return string reversed
 */
string iterative_reverse(string s){
    Stack<char> charStack;

    // Iterate through string characters, adding each to the stack
    for( int i = 0; i < s.length(); i++ ){
        charStack.push(s[i]);
    }

    // Iterate through stack adding each character to a string
    s = ""; // Reset string variable
    while(!charStack.empty()) {
        s += charStack.pop();
    }

    return s;
}


/** 2.
 * @brief Write a recursive method that reverses a string using the runtime stack.
 * Time complexity = O(n)
 * Spacial complexity = O(n)
 * 
 * @param s string to be reversed
 * @return string reversed
 */
string recursive_reverse(string s){
    if (s.length() <= 1) return s; // Base case
    // Add last character + to the next characters in reverse order
    return s[s.length() - 1] + recursive_reverse(s.substr(0, s.length() - 1));
}


/** 3.
 * @brief Write a recursive method that prints the numbers 1 – 50.
 * Time complexity = O(n)
 * Spacial complexity = O(n)
 * 
 * @param n optional int which should not be overriden
 * @return int triangle number
 */
int triangular_number_50(int n){ // Setting a default value of 50 for n
    // Base case                 // instead of having the user pass it in.
    if( n <= 1 )  return 1;

    // Get new n, recursively called down to base case (added to the previous number)
    int result = n + triangular_number_50(n-1);

    // If n gets to the last number, print out the triangular number
    if( n == 50 ){
        cout << "Triangular number of " << n << " = " << result << endl;
    }

    return result;
}


/** 4.
 * @brief Helper funtion for sum(int array[]) so that user doesn't have to pass in 
 * the array index, which should always be 0.
 * 
 * @param array of integers
 * @return sum of numbers in array
 */
int sum(ArrayList<int>& array){
     return recursive_sum(array, 0);
}

/** 4.
 * @brief Write a recursive method sum(int[] array) to calculate the sum of numbers 
 * contained in an array. Decide if you want the  math to occur with the argument 
 * passing or during the return.
 * Time complexity = O(n)
 * Spacial complexity = O(n)
 * 
 * @param array of integers
 * @return sum of numbers in array
 */
int recursive_sum(ArrayList<int>& array, int index){ // Using a helper funtion to 
    // Base case, end of array reached               // pass in the index = 0.
    if( index >= array.length() )  return 0;          

    // Call function recursively to add next numbers in list, similar to Fibonacci
    // although Fibonacci function adds previous number together
    return array.get(index) + recursive_sum(array, index + 1);
}


/**
 * @brief Recursively finds the greatest common devisor of two numbers.
 * Time complexity = O(n)
 * Spacial complexity = O(n)
 * 
 * @param a numerator
 * @param b devisor
 * @return int 
 */
int recursive_gcd(int a, int b){
    if (b == 0) return a;
    else return recursive_gcd(b, a % b);
}


/**
 * @brief Iteratively finds the greatest common denominator of two numbers.
 * Time complexity = O(n)
 * Spacial complexity = O(1)
 * 
 * @param a numerator
 * @param b devisor
 * @return int 
 */
int iterative_gcd(int a, int b){
    int t;
    while( b != 0 ){
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}


/**
 * @brief Finds the fibonacci number at the Nth position. It could be improved with 
 * cache memory. - Improved with memoization
 * Time complexity = O(2^n)
 * Spacial complexity = O(n)
 * 
 * @param n 
 * @return int 
 */
long fibonacci(const long n){ // https://visualgo.net/en/recursion
    // Vector to store results
    vector<long> cache( n+1, -1 );
    
    // Base case
    if (n <= 1)
        return n;

    // If the result is already computed, return it
    if (cache[n] != -1)
        return cache[n];

    // Double recusive calls
    cache[n] = fibonacci(n-1) + fibonacci(n-2);
    return cache[n]; // Return the results
}