#ifndef LIST_TESTS_H
#define LIST_TESTS_H

#include "Linked_List.hpp"
#include "Array_List.hpp"
using namespace std;

/**
 * @brief Tests the Linked List member functions: insert(pos), erase, print, errors.
 * 
 */
void testLinkedListErase(){
    cout << "\nLINKED LIST\n";
    cout << "--Test Erase--\n";

    // List of ints
	LinkedList<int> intList;
    cout << "\nInteger List:\n";
	intList.insert(10, 0);
	intList.insert(11, 1);
	intList.insert(12, 2);
	intList.print();
    intList.erase(0);
    intList.print();

	// List of strings
	LinkedList<string> stringList;
    cout << "\nString List:\n";
	stringList.insert("Harry", 0);
	stringList.insert("Tom", 0);
	stringList.insert("Dick", 1);
	stringList.print();
    stringList.erase(1);
    stringList.print();

	// List of doubles
    cout << "\nDouble List:\n";
	LinkedList<double> doubleList;
	doubleList.insert(12.12, 0);
	doubleList.insert(11.11, 0);
	doubleList.insert(10.10, 0);
    doubleList.print();
    doubleList.erase(2);
	doubleList.print();

    // Test error catching - negative numbers
    try{ doubleList.erase(-1); }
    catch( const out_of_range& e ) { cerr << "Error: " << e.what() << endl; }
    // Test error catching - greater than size
    try{ doubleList.erase(100); }
    catch( const out_of_range& e ) { cerr << "Error: " << e.what() << endl; }
}

/**
 * @brief Tests the Linked List member functions: insert, remove, errors.
 * 
 */
void testLinkedListRemove(){
    cout << "\nLINKED LIST\n";
    cout << "--Test Remove--\n";
    
    // List of chars
	LinkedList<char> charList;
    cout << "\nChar List:\n";
	charList.insert('a');
    charList.insert('a');
	charList.insert('b');
	charList.insert('c');
	charList.print();
    charList.remove('a');
    charList.print();
	
    // List of bools
    cout << "\nBoolean List:\n";
	LinkedList<bool> boolList;
    boolList.insert(true);
	boolList.insert(false);
    boolList.insert(false);
	boolList.insert(true);
	boolList.print();
    boolList.remove(false);
    boolList.print();
	
    // List of floats
    cout << "\nFloat List:\n";
	LinkedList<float> floatList;
	floatList.insert(1.123);
	floatList.insert(2.456);
	floatList.insert(3.789);
    floatList.insert(3.789);
    floatList.print();
    floatList.remove(3.789);
	floatList.print();
    
    // Test error catching - invalid value (should not throw error)
    try{ floatList.remove(4.001); }
    catch( const out_of_range& e ) { cerr << "Error: " << e.what() << endl; }
}

/**
 * @brief Tests the Linked List member functions: length, get, find.
 * 
 */
void testLinkedListFind(){
    cout << "\nLINKED LIST\n";
    cout << "--Test Find--\n";
    // List of size_t
	LinkedList<size_t> size_tList;
    cout << "\nInteger List:\n";
	size_tList.insert(10);
	size_tList.insert(11);
	size_tList.insert(12);
    size_tList.insert(13);
    size_tList.insert(14);
    size_tList.insert(15);
    cout << "Leng: " << size_tList.length() << "\n";
    cout << "Peek: " << size_tList.peek() << "\n";
	cout << "Get0: " << size_tList.get(0) << "\n";
    cout << "Get1: " << size_tList.get(1) << "\n";
	cout << "Get2: " << size_tList.get(2) << "\n";
    cout << "Find: " << size_tList.find(10) << "\n";
    cout << "Find: " << size_tList.find(12) << "\n";
    cout << "Find: " << size_tList.find(15) << "\n";
    cout << "Find: " << size_tList.find(16) << endl;
}

/**
 * @brief Tests the Linked List member functions: add, count, remove_duplicates, reverse, append.
 * 
 */
void testLinkedListFuncs(){
    cout << "\nLINKED LIST\n";
    cout << "Test Count\n";

    LinkedList<int> intList;
	intList.add(12);
    intList.add(10);
    intList.add(13);
    intList.add(14);
    intList.add(10);
    intList.add(11);
    intList.print();
    cout << "Count10: " << intList.count(10) << "\n";
    cout << "Count12: " << intList.count(12) << "\n";
    cout << "Count--: " << intList.count(1) << "\n";
    
    cout << "\nRemove Duplicates\n";
    intList.remove_duplicates();
    intList.print();
    
    cout << "\nReverse\n";
    intList.reverse();
    intList.print();
    
    cout << "\nAppend List\n";
    LinkedList<int> newList;
    newList.add(2);
    newList.add(3);
    newList.add(4);
    intList.append(newList);
    intList.print();
}

/**
 * @brief Test the Array List member function: insert(pos), erase, print, errors
 * 
 */
void testArrayListErase(){
    cout << "\nARRAY LIST\n";
    cout << "--Test Erase--\n";

    // List of ints
	ArrayList<int> intList;
    cout << "\nInteger List:\n";
	intList.insert(10, 0);
	intList.insert(11, 1);
	intList.insert(12, 2);
	intList.print();
    intList.erase(0);
    intList.print();

	// List of strings
	ArrayList<string> stringList;
    cout << "\nString List:\n";
	stringList.insert("Harry", 0);
	stringList.insert("Tom", 0);
	stringList.insert("Dick", 1);
	stringList.print();
    stringList.erase(1);
    stringList.print();

	// List of doubles
    cout << "\nDouble List:\n";
	ArrayList<double> doubleList;
	doubleList.insert(12.12, 0);
	doubleList.insert(11.11, 0);
	doubleList.insert(10.10, 0);
    doubleList.print();
    doubleList.erase(2);
	doubleList.print();

    // Test error catching - negative numbers
    try{ doubleList.erase(-1); }
    catch( const out_of_range& e ) { cerr << "Error: " << e.what() << endl; }
    // Test error catching - greater than size
    try{ doubleList.erase(100); }
    catch( const out_of_range& e ) { cerr << "Error: " << e.what() << endl; }
}

/**
 * @brief Test the Array List member function: insert, remove, errors
 * 
 */
void testArrayListRemove(){
    cout << "\nARRAY LIST\n";
    cout << "--Test Remove--\n";

    // List of chars
	ArrayList<char> charList;
    cout << "\nChar List:\n";
	charList.insert('a');
    charList.insert('a');
	charList.insert('b');
	charList.insert('c');
	charList.print();
    charList.remove('a');
    charList.print();

	// List of bools
    cout << "\nBoolean List:\n";
	ArrayList<bool> boolList;
    boolList.insert(true);
	boolList.insert(false);
    boolList.insert(false);
	boolList.insert(true);
	boolList.print();
    boolList.remove(false);
    boolList.print();

	// List of floats
    cout << "\nFloat List:\n";
	ArrayList<float> floatList;
	floatList.insert(1.123);
	floatList.insert(2.456);
	floatList.insert(3.789);
    floatList.insert(3.789);
    floatList.print();
    floatList.remove(1.123);
	floatList.print();

    // Test error catching - invalid value (should not throw error)
    try{ floatList.remove(4.001); }
    catch( const out_of_range& e ) { cerr << "Error: " << e.what() << endl; }
}

/**
 * @brief Tests the Array List member functions: length, get, find.
 * 
 */
void testArrayListFind(){
    cout << "\nARRAY LIST\n";
    cout << "--Test Find--\n";

    // List of size_t
	ArrayList<size_t> size_tList;
    cout << "\nInteger List:\n";
	size_tList.insert(10);
	size_tList.insert(11);
	size_tList.insert(12);
    size_tList.insert(13);
    size_tList.insert(14);
    size_tList.insert(15);
    cout << "Leng: " << size_tList.length() << "\n";
    cout << "Peek: " << size_tList.peek() << "\n";
	cout << "Get0: " << size_tList.get(0) << "\n";
    cout << "Get1: " << size_tList.get(1) << "\n";
	cout << "Get2: " << size_tList.get(2) << "\n";
    cout << "Find: " << size_tList.find(10) << "\n";
    cout << "Find: " << size_tList.find(12) << "\n";
    cout << "Find: " << size_tList.find(15) << "\n";
    cout << "Find: " << size_tList.find(16) << endl;
}

/**
 * @brief Tests the Array List member functions: add, count, remove_duplicates, reverse, append.
 * 
 */
void testArrayListFuncs(){
    cout << "\nARRAY LIST\n";
    cout << "--Test Erase--\n";

    // List of ints
	ArrayList<int> intList;
    cout << "\nInteger List:\n";
	intList.add(10);
    intList.add(11);
    intList.add(12);
    intList.add(10);
    intList.add(13);
    intList.add(14);
    intList.add(10);
    intList.add(11);
    intList.print();
    cout << "Count10: " << intList.count(10) << "\n";
    cout << "Count12: " << intList.count(12) << "\n";
    cout << "Count--: " << intList.count(1) << "\n";
    
    cout << "\nRemove Duplicates\n";
    intList.remove_duplicates();
    intList.print();
    
    cout << "\nReverse\n";
    intList.reverse();
    intList.print();
    
    cout << "\nAppend List\n";
    ArrayList<int> newList;
    newList.add(2);
    newList.add(3);
    newList.add(4);
    intList.append(newList, newList.length());
    intList.print();
}

/**
 * @brief Call all of test functions.
 * 
 */
void runTests(){
    testLinkedListErase();
    testLinkedListRemove();
    testLinkedListFind();
    testLinkedListFuncs();
    testArrayListErase();
    testArrayListRemove();
    testArrayListFind();
    testArrayListFuncs();
}

#endif