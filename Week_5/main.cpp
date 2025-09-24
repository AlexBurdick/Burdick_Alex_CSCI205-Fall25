/*********************************************************************
 * @file  main.cpp
 * 
 * @brief Entry point for the dorm assignement program.
 *********************************************************************/

#include <unordered_map>
#include <string>
#include <stdexcept>
#include "list_tests.cpp"
#include "Student.h"
using namespace std;

int main(){
    unordered_map <string, int> dorms;
    dorms["Gryffindor"] = 0;
    dorms["Slytherin"]  = 1;
    dorms["Ravenclaw"]  = 2;
    dorms["Hufflepuff"] = 3;

    testRemoveAt();
    testRemove();
    testFind();

    return 0;
}