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

	for( int i = 0; i < 5; i++ ){
		//nums.push_front(5);
	}
	
	nums.push_front(1);
	nums.push_back(4);
	nums.push_front(2);
	nums.push_back(5);
	nums.push_front(3);
	nums.push_back(6);

	cout << "i0: " << nums.getIndex(0) << "\n";
	cout << "i9: " << nums.getIndex(9) << "\n";
	cout << "i1: " << nums.getIndex(1) << "\n";
	cout << "i8: " << nums.getIndex(8) << "\n";
	cout << "i2: " << nums.getIndex(2) << "\n";
	cout << "i7: " << nums.getIndex(7) << "\n";

	
	while( !nums.empty() ){
		int a = nums.pop_front();
		cout << "Number is: " << a << endl;
	}

	return 0;
}