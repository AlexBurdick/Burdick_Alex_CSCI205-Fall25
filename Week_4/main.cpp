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
#include "infix_converter.cpp"

using namespace std;

// Function prototypes
void testDeque();
void testQueue();
void testStack();
void testInfixToPostfix();
void testParChecker();
void testPostfixEvaluator();
void testInfixEvaluator();

int main(){
	testDeque();
	/** testQueue();
	testStack();
	testParChecker(); 
	testInfixToPostfix();
	testPostfixEvaluator();
	testInfixEvaluator(); */
	return 0;
}

void testDeque(){
	cout << "\n--DEQUE--\n";
	// Test default instantiation
	cout << "Default Instantiation:\n";
	int sizeDeque = 200; // Will be larger than initial size of the deque
	Deque<bool> bools; // Create a smaller deque to be expanded, default = 100
	
	// Test member functions
	cout << "Size:  " << bools.size() << "\n";
	cout << "Full:  " << bools.full() << "\n";
	cout << "Empty: " << bools.empty() << "\n";
	
	// Test resize
	for( int i = 0; i < sizeDeque; i++ ){ // Deque will have to resize
		bools.push_back( (i%2 == 0 ) ? true : false );
	}
	
	// Test member functions
	cout << "Size:  " << bools.size() << "\n";
	cout << "Full:  " << bools.full() << "\n";
	cout << "Empty: " << bools.empty() << "\n";
	cout << "Front: " << bools.front() << "\n";
	cout << "Back:  " << bools.back() << "\n";
	
	// Test int instantiation, and integer data type
	cout << "\nInt Instantiation:\n";
	Deque<int> nums(11);
	// Test push front/back, pop front/back
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
	
	// Test array instantiaion, and char datatype
	cout << "\nArray Instantiation:\n";
	char arr[] = {'a', 'b', 'c', 'd', 'e'};
	size_t size = 5;
	Deque<char> chars(arr, size);
	cout << "While !chars.empty:" << "\n";
	while( !chars.empty() ){
		cout << chars.pop_back() << "\n";
	}
	cout << "Size: " << chars.size() << endl;
}

void testQueue(){
	cout << "\n--QUEUE--\n";
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
	cout << "\n--STACK--\n";
	Stack<int> ns(3);
	ns.push(22);
	ns.push(33);
	ns.push(44);
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
	cout << "\n--Infix-to-Postfix--\n";
	string equation = "A+ B /(C*D) - E"; // Default value
	string postfix;
	postfix = infixToPostfix(equation);
	cout << "Prefix:  " << equation << "\n";
	cout << "Postfix: " << infixToPostfix(postfix) << endl;
}

void testParChecker(){
	cout << "\n--Parentheses balance check--\n";
	string parens = "(((()())())()))"; // Default value
	bool isBalanced = parChecker(parens);
	cout << "Parentheses are balanced? " << (isBalanced ? "Yes" : "No") << endl;
}

void testPostfixEvaluator(){
	cout << "\n--Postfix Evaluation--\n";
	string expr = "234*+5+";
	int result = postfixEvaluator(expr);
	cout << "Postfix eval = " << result << endl;
}

void testInfixEvaluator(){
	cout << "\n--Infix Evaluation--\n";
	string expr = "234*+5+";
	int result = infixEvaluator(expr);
	cout << "Infix eval = " << result << endl;
}