/*********************************************************************
 * @file  main.cpp
 * 
 * @brief Entry point for the dorm assignement program.
 *********************************************************************/

#include <random>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <vector>
#include "Linked_List.hpp"
#include "Array_List.hpp"
#include "list_tests.hpp"
#include "Student.h"
using namespace std;

// Function prototypes
void assignDorm(Student, unordered_map<string, LinkedList<Student>>&);

int main(){
    // Create a hash map to hold dorm names
    unordered_map<string, LinkedList<Student>> dormMap;
    
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
        while( getline(newfile, record )){
            // Slice string
            int pos = record.find(" "); // Get position of delimiter
            int id = stoi( record.substr(0, pos) ); // Get first part
            string name = record.substr( pos+1, record.size() ); // Get second part
            Student stu = Student(id, name); // use the string to create a Student object
            assignDorm(stu, dormMap); // Assign student to a dorm
        }
        newfile.close();   //close the file object.
    }

    // Write dorm rosters to files - the_dorm_name.txt
    for( auto& pair : dormMap ){
        string dorm = pair.first;
        string filename = dorm + ".txt";
        ofstream rosterFile(filename);
        rosterFile << dorm << endl;
        
        Node<Student>* current = pair.second.getHead();
        while( current != nullptr ){
            rosterFile << current->payload.getID() << " " << current->payload.getName() << endl;
            current = current->next;
        }
    }

    //runTests();

    return 0;
}

/**
 * @brief Function to add a Student to a dorm's list
 * 
 * @param dormMap
 * @param student
 */
void assignDorm(Student student, unordered_map<string, LinkedList<Student>>& dormMap){
    int minLen = INT_MAX; // Stores the smallest list length
    vector<string> minDorms; // Vector to store dorms with the minimum length

    for( auto& pair : dormMap ){
        int len = pair.second.length();
        if( len < minLen ){
            minLen = len;
            minDorms.clear(); // Clear previous entries
            minDorms.push_back(pair.first);
        } else if (len == minLen) {
            minDorms.push_back(pair.first); // Add to the list of minimum dorms
        }
    }
    
    // Randomly select a dorm if there is a tie
    if (!minDorms.empty()) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(0, minDorms.size() - 1);
        int randomIndex = distrib(gen);
        string selectedDorm = minDorms[randomIndex];

        // Assign the student to the selected dorm
        dormMap[selectedDorm].add(student);
    }
}