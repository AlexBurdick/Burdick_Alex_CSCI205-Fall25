/*********************************************************************
 * @file  main.cpp
 * 
 * @brief Main function for the Stacks, Queues, Deques Lab Assignment
 *********************************************************************/

#include <iostream>
#include <string>
#include "Card.h"
#include "Deque.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "Converters.cpp"

using namespace std;

// Function prototypes
void testDeque();
void testQueue();
void testStack();
void testInfixToPostfix();
void testParChecker();

int main(){
	testDeque();
	testQueue();
	testStack();
	testInfixToPostfix();
	testParChecker();
	return 0;
}

void testDeque(){
	cout << "\nDEQUE\n";
	Deque<int> nums(11);
	
	nums.push_front(42);
	nums.push_back(12);
	nums.push_back(27);
	nums.push_back(92);
	nums.push_front(86);
	nums.push_front(53);

	cout << "Pop front: " << nums.pop_front() << "\n";
	cout << "Pop back:  " << nums.pop_back() << "\n";
	cout << "Get back:  " << nums.back() << "\n";

	nums.push_front(19);

	cout << "Pop back:  " << nums.pop_back() << "\n";
	cout << "Pop back:  " << nums.pop_back() << "\n";
	cout << "Pop back:  " << nums.pop_back() << "\n";

	nums.push_back(67);
	nums.push_back(117);
	
	cout << "Get front: " << nums.front() << "\n";
	
	int sizeDeque = 6; // Will be larger than initial size of the deque
	Deque<int> ns(sizeDeque/2); // Create a smaller deque to be expanded
	cout << "Push front:" << "\n";
	for( int i = 0; i < sizeDeque; i++ ){ // Deque will have to resize
		ns.push_back(i);
	}
	
	cout << "While !ns.empty:" << "\n";
	while( !ns.empty() ){
		int a = ns.pop_back();
		cout << "Number is: " << a << "\n";
	}
	cout << "Size: " << ns.size() << endl;
}

void testQueue(){
	cout << "QUEUE\n";
	Queue<int> nums(3);
	nums.enqueue(10);
	nums.enqueue(20);
	nums.enqueue(30);

	cout << "Empty: " << nums.empty() << "\n";
	cout << "Full: " << nums.full() << "\n";
	cout << "Size: " << nums.size() << "\n";
	cout << nums.dequeue() << "\n";
	cout << nums.dequeue() << "\n";
	cout << nums.dequeue() << "\n";
	cout << "Empty: " << nums.empty() << "\n";
	cout << "Full: " << nums.full() << "\n";
	cout << "Size: " << nums.size() << endl;
}

void testStack(){
	cout << "\nSTACK\n";
	Stack<int> ns(3);
	ns.push(22);
	ns.push(33);
	ns.push(44);
	cout << "\nSTACK\n";
	cout << "Empty: " << ns.empty() << "\n";
	cout << "Full: " << ns.full() << "\n";
	cout << "Size: " << ns.size() << "\n";
	cout << ns.pop() << "\n";
	cout << ns.pop() << "\n";
	cout << ns.pop() << "\n";
	cout << "Empty: " << ns.empty() << "\n";
	cout << "Full: " << ns.full() << "\n";
	cout << "Size: " << ns.size() << endl;
}

void testInfixToPostfix(){
	string equation = "A+ B /(C*D) - E"; // Default value
	// Get user input for an equation written in infix notation
	cout << "Equation (infix notation): ";
	cin >> equation;
	cout << "Prefix:  " << equation << "\n";
	cout << "Postfix: " << infixToPostfix(equation) << endl;
}

void testParChecker(){
	string parens = "((())())"; // Default value
	// Get user input for a series of parentheses
	cout << "Parentheses: ";
	cin >> parens;
	bool isBalanced = parChecker(parens);
	cout << "Parentheses are balanced? " << (isBalanced ? "Yes" : "No") << endl;
}