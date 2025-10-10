#include <iostream>
#include <sstream>
#include <vector>
#include <array>
#include <string>
#include "Deque.hpp"
#include "Stack.hpp"
#include "ArrayList.hpp"
#include "LinkedList.hpp"
#include "towers_main.cpp"

using namespace std;

// Function prototypes
int recursive_gcd(int a, int b);
int iterative_gcd(int a, int b);
long fibonacci(const long n);
string iterative_reverse(string s);
string recursive_reverse(string s);
int triangular_number_50(int n = 50);
int sum(ArrayList<int>& array);
int recursive_sum(ArrayList<int>&, int index);
int len(int n);
int numEars(int n);
string strip(string text, char letter);
bool parens(string s);
stringstream printList(LinkedList<char>&);

int main(){
    /** 
    // Fibonacci
    int n;
    cout << "--Testing Fibonacci Function--\n";
    cout << "Enter a number: ";
    cin >> n;
    cout << "The " << n << "th Fibonacci number is " << fibonacci(n) << endl;
    */
    // GCD
    int a = 12;
    int b = 8;
    cout << "\n--Testing recursive GCD Function--\n";
    recursive_gcd(a, b);
    /**
    // 1. String reverse (iterative)
    string s;
    cout << "\n--Testing Iterative String Reverse Function--\n";
    cout << "Enter a string: ";
    cin >> s;
    cout << "Reversed string: " << iterative_reverse(s) << endl;
    
    // 2. String reverse (recursive)
    cout << "\n--Testing Recursive String Reverse Function--\n";
    cout << "Enter a string: ";
    cin >> s;
    cout << "Reversed string: " << recursive_reverse(s) << endl;

    // 3. Triangular number
    cout << "\n--Testing Triangular number Function--\n";
    cout << "Triangular number of 50 = " << triangular_number_50() << endl;

    // 4. Array sum
    cout << "--Testing Array Sum Function--\n";
    ArrayList<int> intList = {1, 2, 3, 4}; // list for testing, sum = 10
    cout << "\n--Testing Recursive Array Sum--\n";
    cout << "The sum of the array is " << sum(intList) << endl;
    
    // 5. Number of digits
    cout << "--Testing Number of Digits Function--\n";
    cout << "Enter a number: ";
    cin >> n;
    cout << "There are " << len(n) << " digits in " << n << endl;

    // 6. Puppies ears
    cout << "--Testing Ears Counting function--\n";
    cout << "Enter the number of puppies: ";
    cin >> n;
    cout  << n << " puppies have " << numEars(n) << " ears " << endl;

    // 7. String strip
    char c;
    cout << "\n--Testing Strip String Function--\n";
    cout << "Enter a string: ";
    cin >> s;
    cout << "Enter a character: ";
    cin >> c;
    cout << "Stripped string: " << strip(s, c) << endl;
    
    // 8. Parentheses
    cout << "\n--Testing Parentheses Function--\n";
    cout << "Enter a string: ";
    cin >> s;
    cout << "Parentheses balanced = " << parens(s) << endl;
    
    // 9. Recursive Linked List Print (in Linked_List.hpp)
    LinkedList<char> list = {'a', 'b', 'c', 'd'};
    cout << "\n--Testing Linked List Print Function--\n";
    cout << "Printing list: " << list << endl;

    //10. Recursive Reverse Linked List (in Linked_List.hpp)
    cout << "\n--Testing Linked List Reverse Function--\n";
    list.reverse();
    cout << "Reversed list: " << list << endl;
    */
    cout << "--Testing Towers of Hanoi Function--\n";
    //towers_of_hanoi();
    moveTower(3, 'A', 'B', 'C');
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


/** 5.
 * @brief Write a recursive method len(int n) to count the digits of a given integer. 
 * Do not treat it as a String.
 * Time complexity = O(n)
 * Spacial complexity = O(n)
 * 
 * @param n number to be sized
 * @return int size of input
 */
int len(int n){
    // Base case if n is a single digit (<10)
    if ( n < 10 ) return 1;

    // Each call should return 1, added together for total number of digits
    return 1 + len( n/10 );
}


/** 6.
 * @brief Puppies standing in a line, numbered 1, 2,...N. Odd puppies (1, 3,...) have 
 * 2 ears. Even puppies (2, 4,...) have 3 ears. Recursively return the number of "ears" 
 * in the puppy line 1, 2,...N.
 * Time complexity = O(n)
 * Spacial complexity = O(n)
 * 
 * @param n number of puppies
 * @return int total number of ears
 */
int numEars(int n){
    // Base case is n == 1
    if ( n <= 1 ) return 2;

    if ( n % 2 == 0 ) return 3 + numEars(n-1); // If even
    else return 2 + numEars(n-1);              // Else must be odd
}


/** 7.
 * @brief Write the recursive method that accepts a String and a  character and 
 * recursively “cleanses” the string of that character.
 * Time complexity = O(n)
 * Spacial complexity = O(n)
 * 
 * @param n number of puppies
 * @return int total number of ears
 */
string strip(string text, char c) {
    // Base case: empty , to test validate inpupt (from Le Chat 10/05/2025)
    if( text.empty() ) return "";
    
    // Base case 1 character in string
    if (text.length() == 1) {
        if (text[0] == c) {
            return "";
        } else {
            return string(1, text[0]);
        }
    }

    // Get the first character
    char firstChar = text[0];
    // Choose operator from Le Chat (10/05/2025)
    string firstCharStr = (firstChar == c) ? "" : string(1, firstChar);

    // Recursively process the rest of the string
    return firstCharStr + strip(text.substr(1), c);
}


/** 8.
 * @brief Given a string, return true if it is a nesting of zero or more pairs of 
 * parentheses, like "(())" or "((()))".
 * Time complexity = O(n)
 * Spacial complexity = O(n)
 * 
 * @param n number of puppies
 * @return int total number of ears
 */
bool parens(string s){
    // Base case string length 0
    if( s.empty() ) return true;

    // Get the first and last characters to compare
    char firstChar = s.front();
    char lastChar  = s.back();
    
    // Test to see if paranetheses are proper, if so recurse
    if( firstChar == '(' && lastChar == ')' ){
        return parens( s.substr( 1, s.length()-2) );
    // Any other outcome is considered false
    } else return false;
}


/** 9.
 * @brief Modify the print() method from your Linked List class to use recursion 
 * instead of iteration. Found in the overloaded output operator and it's helper 
 * function (recursivePrint).
 * Time complexity = O(n)
 * Spacial complexity = O(n)
 * 
 * @param n number of puppies
 * @return int total number of ears
 */

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
    cout << a << "/" << b << "\n";
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