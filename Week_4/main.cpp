/*
	To build this app run: 
		g++ -Wall -pedantic main.cpp Card.cpp
	
	Do not include Deque.hpp in the build command. The hpp code
	will be copied by the preprocessor into main.cpp. This is
	possible because the Deque class is a template class. The
	compiler will generate the appropriate code for the template
	class when it is used in main.cpp.

	All references to generic type T in Deque.hpp will be replaced
	with the appropriate type
*/

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

using namespace std;

int main(){
	// Deque of integers
	Deque<int> nums(10);

	for( int i = 0; i < 20; i++ ){
		nums.push_front(5);
	}
	
	cout << "Front: " << nums.getFront() << "\n";
	cout << "Back:  " << nums.getFront() << "\n";

	while( !nums.empty() ){
		int a = nums.pop_back();
		cout << "Number is: " << a << endl;
	}

	return 0;
}