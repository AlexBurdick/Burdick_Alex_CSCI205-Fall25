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
	/** Deque of integers
	Deque<int> nums(11);
	
	nums.push_front(42);
	nums.push_back(12);
	nums.push_back(27);
	nums.push_back(92);
	nums.push_front(86);
	nums.push_front(53);

	cout << "Pop front: " << nums.pop_front() << "\n";
	cout << "Pop back:  " << nums.pop_back() << "\n";
	cout << "Get back:  " << nums.getBack() << "\n";

	nums.push_front(19);
	nums.push_back(117);

	cout << "Pop back:  " << nums.pop_back() << "\n";
	cout << "Pop back:  " << nums.pop_back() << "\n";
	cout << "Pop back:  " << nums.pop_back() << "\n";
	cout << "Pop back:  " << nums.pop_back() << "\n";
	cout << "Pop back:  " << nums.pop_back() << "\n";
	cout << "Pop back:  " << nums.pop_back() << "\n";
	cout << "Size:  " << nums.getSize() << "\n";
	*/
	int sizeDeque = 6;
	Deque<int> ns(sizeDeque/2);
	cout << "Push front:" << "\n";
	for( int i = 0; i < sizeDeque; i++ ){
		ns.push_back(i);
	}
	ns.printDeque(sizeDeque);
	/** 
	cout << "Push back:" << "\n";
	Deque<int> nums(sizeDeque);
	for( int i = 0; i < sizeDeque; i++ ){
		nums.push_back(i);
	}
	*/
	cout << "While !ns.empty:" << "\n";
	while( !ns.empty() ){
		int a = ns.pop_back();
		cout << "Number is: " << a << "\n";
	}
	cout << "Size: " << ns.getSize() << endl;
	
	return 0;
}