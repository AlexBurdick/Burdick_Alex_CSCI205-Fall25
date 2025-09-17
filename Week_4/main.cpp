/*********************************************************************
 * @file  main.cpp
 * 
 * @brief Main funciton for the Abstract Data Types lab.
 *********************************************************************/

#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<int> myStack;

    // Example usage: push some values
    myStack.push(10);
    myStack.push(20);
    ;myStack.push(30);

    // Push a value and return the result of a pop
    int poppedValue = myStack.top();
    myStack.pop();
    cout << "Popped value: " << poppedValue << endl;

    int popV = myStack.pop();

    return 0;
}