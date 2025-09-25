#include "Linked_List.hpp"
#include "Array_List.hpp"
#include "Student.h"
using namespace std;

void testRemoveAt(){
    // List of ints
	LinkedList<int> intList;
    cout << "\nInteger List:\n";
	intList.insert(10, 0);
	intList.insert(11, 1);
	intList.insert(12, 2);
	intList.printList();
    intList.removeAt(0);
    intList.printList();

	// List of strings
	LinkedList<string> stringList;
    cout << "\nString List:\n";
	stringList.insert("Harry", 0);
	stringList.insert("Tom", 0);
	stringList.insert("Dick", 1);
	stringList.printList();
    stringList.removeAt(1);
    stringList.printList();

	// List of doubles
    cout << "\nDouble List:\n";
	LinkedList<double> doubleList;
	doubleList.insert(12.12, 0);
	doubleList.insert(11.11, 0);
	doubleList.insert(10.10, 0);
    doubleList.printList();
    doubleList.removeAt(2);
	doubleList.printList();
    
    // Test error catching - negative numbers
    try{
        doubleList.removeAt(-1);
    } catch( const out_of_range& e ) {
        cerr << "Error: " << e.what() << endl;
    }
    // Test error catching - greater than size
    try{
        doubleList.removeAt(100);
    } catch( const out_of_range& e ) {
        cerr << "Error: " << e.what() << endl;
    }
}

void testRemove(){
    // List of ints
	LinkedList<char> charList;
    cout << "\nChar List:\n";
	charList.insert('a');
    charList.insert('a');
	charList.insert('b');
	charList.insert('c');
	charList.printList();
    charList.remove('a');
    charList.printList();

	// List of strings
    cout << "\nBoolean List:\n";
	LinkedList<bool> boolList;
    boolList.insert(true);
	boolList.insert(false);
    boolList.insert(false);
	boolList.insert(true);
	boolList.printList();
    boolList.remove(false);
    boolList.printList();

	// List of doubles
    cout << "\nFloat List:\n";
	LinkedList<float> floatList;
	floatList.insert(1.123);
	floatList.insert(2.456);
	floatList.insert(3.789);
    floatList.insert(3.789);
    floatList.printList();
    floatList.remove(3.789);
	floatList.printList();
    
    // Test error catching - invalid value
    try{
        floatList.remove(4.001);
    } catch( const out_of_range& e ) {
        cerr << "Error: " << e.what() << endl;
    }
}

void testFind(){
    // List of ints
	LinkedList<int> intList;
    cout << "\nInteger List:\n";
	intList.insert(10);
	intList.insert(11);
	intList.insert(12);
    intList.insert(13);
    intList.insert(14);
    intList.insert(15);
    cout << "Leng: " << intList.length() << "\n";
    cout << "Peek: " << intList.peek() << "\n";
	cout << "Get0: " << intList.get(0) << "\n";
    cout << "Get1: " << intList.get(1) << "\n";
	cout << "Get2: " << intList.get(2) << "\n";
    cout << "Find: " << intList.find(10) << "\n";
    cout << "Find: " << intList.find(12) << "\n";
    cout << "Find: " << intList.find(15) << "\n";
    cout << "Find: " << intList.find(16) << endl;
}