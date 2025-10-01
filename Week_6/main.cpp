#include <iostream>
#include <vector>
#include "Deque.hpp"
#include "Stack.hpp"
#include "Array_List.hpp"
#include "Linked_List.hpp"

using namespace std;

int euclid_gcd(int a, int b);
long fibonacci(const long n);

int main(){
    int n;
    cout << "Enter a number: ";
    cin >> n;
    cout << "\nThe " << n << "th Fibonacci number is " << fibonacci(n) << endl;
}

int euclid_gcd(int a, int b){
    if (b == 0) return a;
    else return euclid_gcd(b, a % b);
}

/**
 * @brief Finds the fibonacci number at the Nth position. It could be improved with 
 * cache memory.
 * Time complexity = O(2^n)
 * Spacial complexity = O(n)
 * 
 * @param n 
 * @return int 
 */
long fibonacci(const long n){ // https://visualgo.net/en/recursion
    // Memoization
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