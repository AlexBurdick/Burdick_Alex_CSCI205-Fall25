/*********************************************************************
 * @file  main.cpp
 * 
 * @brief Entry point for the dorm assignement program.
 *********************************************************************/

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include "Linked_List.hpp"
#include "Array_List.hpp"
#include "list_tests.hpp"
#include "Student.h"
using namespace std;

int main(){
    // Create a hash map to hold dorm names
    unordered_map <string, LinkedList<Student>> dormMap;
    
    // Open dorm file and read into the hash map
    fstream newfile;
    newfile.open("dormFile.txt", ios::in); //open a file to perform read operation using file object
    if( newfile.is_open() ){   //checking whether the file is open
        string dorm;
        while(getline(newfile, dorm)){  //read data from file object and put it into string.
            dormMap[dorm] = LinkedList<Student>(); // use the string as the key for a new element in hash map
        }
        newfile.close();   //close the file object.
    }

    newfile.open("studentFile.txt", ios::in);
    if( newfile.is_open() ){
        string record;
        while( getline(newfile, record )){  //read data from file object and put it into string.
            // Slice string
            int pos = record.find(" "); // Get position of delimiter
            int id = stoi( record.substr(0, pos) ); // Get first part
            string name = record.substr( pos+1, record.size() ); // Get second part
            
            Student stu = Student(id, name); // use the string to create a Student object
        }
        newfile.close();   //close the file object.
    }


    //runTests();

    return 0;
}