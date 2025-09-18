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

	Queue<int> nums(3);
	cout << "STACK\n";
	nums.enqueue(42);
	nums.enqueue(12);
	nums.enqueue(27);
	cout << nums.size() << endl;
	cout << nums.dequeue() << endl;
	cout << nums.dequeue() << endl;
	cout << nums.dequeue() << endl;
	cout << nums.size() << endl;

/** 
	Deque of integers
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

	cout << "Pop back:  " << nums.pop_back() << "\n";
	cout << "Pop back:  " << nums.pop_back() << "\n";
	cout << "Pop back:  " << nums.pop_back() << "\n";

	nums.push_back(67);
	nums.push_back(117);
	
	nums.print();
	 */
	/**
	int sizeDeque = 6;
	Deque<int> ns(sizeDeque/2);
	cout << "Push front:" << "\n";
	for( int i = 0; i < sizeDeque; i++ ){
		ns.push_back(i);
	}
	ns.printDeque(sizeDeque);
	
	cout << "While !ns.empty:" << "\n";
	while( !ns.empty() ){
		int a = ns.pop_back();
		cout << "Number is: " << a << "\n";
	}
	cout << "Size: " << ns.size() << endl;
	*/
	
	return 0;
}