#include "Fraction.h"
#include "Fraction.cpp"
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>

using namespace std;


// ****NOTE FOR CLASS****
/** text right above Exploration 1.12.9. Overloading Addition, 
 *  what are they talking about?  */

/**
 * @brief Finds the largest fraction
 * @param vector location
 * @return largest fraction
 * 
 * Iterates through the vector of fractions to find the largest. This function is not
 * in the implementation file for Fraction (Fraction.cpp) so that it would not need 
 * to include the array library, which would increase the time it takes to compile.
 */
Fraction find_largest(const vector<Fraction>& fractions) {
    
    Fraction largest = fractions[0]; /**< Set first fraction as largest */
    
    // Loop through each element in the vector 
    for (int i=0; i<fractions.size(); i++) {
        if (fractions[i] > largest) { /**< If the next is larger */
            largest = fractions[i];   /**< set it as new largest */
        }
    }

    return largest;
}


/**
 * @brief Function that prints fractions
 * @param fractions Location of vector of Fractions
 * 
 * Prints fractions in rows of 5.This function is not
 * in the implementation file for Fraction (Fraction.cpp) so that it would not need 
 * to include the array library, which would increase the time it takes to compile.
 * 
 * Nested loop structure and formatting elements suggested by LeoAI (08/24/2025).
 */
void print(const vector<Fraction>& fractions)
{
    int num_columns = 5; /** Number of items per row (columns ) */
    int column_width = 10; /** Width of each column ) */    
    // Loop through each column
    for (int i=0; i<fractions.size(); i+=num_columns) {
        // Loop through row
        for (int j=0; j<num_columns; j++) {
            // Make sure index is still in bounds
            if (i+j < fractions.size()) { 
                cout << left << setw(column_width) << fractions[i+j];
            }
        }
        cout << "\n";
    }
    // Print extra line and clear stream
    cout << endl;
}


/**
 * @brief Main function
 * @return 0 or 1 if there are errors
 * 
 * Runs the program
 */
int main()
{
    string separator = "\n--------------------\n"; /**< Used for formatting output */
    // Open a file with fraction values, and vector to store them
    ifstream file; /**< This will hold the file we read from */
    string file_name = "fractions.txt"; /**< File containing list of fractions */
    file.open(file_name); /**< ifstream defaults to ios::in */
    
    vector<Fraction> fraction_vector; /**< Stores data from the file */
    fraction_vector.reserve(100); /**< Sets aside memory, already knowing file length */

    // Read file into vector
    if (file.is_open()) {   /**< Confirm the file is open */
        string line;
        while(getline(file, line)) { /**< Read each line into a string */
            /**
             * I found an explanation of the substring function on Geeks for 
             * Geeks. I chose to find the position of the comma and use that to 
             * get the two parts of the fraction, then convert them to integers.
             * 
             * Geeks for Geeks. n.d. substr() in C++. geeksforgeeks.org.
             * https://www.geeksforgeeks.org/cpp/substring-in-cpp/
             */
            int pos = line.find(","); /**< Get index of comma */
            
            string sub_n = line.substr(0, pos); /**< Get substring before of comma */
            string sub_d = line.substr(pos+1); /**< Get substring after of comma */
            
            int n = stoi(sub_n); /**< Convert to integer */
            int d = stoi(sub_d);
            
            fraction_vector.push_back(Fraction(n,d)); /**< Add Fraction to end of vector */
        }
        file.close();   /**< Close the file object */
    }
    else { /**< If the file is not open */
        cout << "No open file";
        return 1; 
    }
    cout << "Fractions in " << file_name << " - \n";
    print(fraction_vector);
    Fraction largest_fraction = find_largest(fraction_vector);
    cout << "** The largest fraction is: " << largest_fraction << endl;

    
    // Math tests
    Fraction x(11, 17);
    Fraction y(2, 4);
    cout << separator << "Math operator tests: \n";
    cout << x << " + " << y << " = " << x+y << "\n"; // add
    cout << x << " - " << y << " = " << x-y << "\n"; // subract
    cout << x << " * " << y << " = " << x*y << "\n"; // mupltiply
    cout << x << " / " << y << " = " << x/y << "\n"; // divide
    

    // Comparison tests
    cout << separator << "Comparison operator tests: \n";
    // equals
    if (x==y) { cout << x << " equals " << y << "\n"; }
    else      { cout << x << " not equals " << y << "\n"; }
    // not equals
    if (x!=y) { cout << x << " not equals " << y << "\n"; }
    else      { cout << x << " equals " << y << "\n"; }
    // greater than
    if (x>y)  { cout << x << " greater than " << y << "\n"; }
    else      { cout << x << " not greater than " << y << "\n"; }
    // less than
    if (x<y)  { cout << x << " less than " << y << "\n"; }
    else      { cout << x << " not less than " << y << "\n"; }
    // greater than equals
    if (x>=y) { cout << x << " greater equals " << y << "\n"; }
    else      { cout << x << " not greater equals " << y << "\n"; }
    // less than equals
    if (x<=y) { cout << x << " less equals " << y << "\n"; }
    else      { cout << x << " not less equals " << y << "\n"; }


    // Assignment operator tests
    cout << separator << "Assignment operator tests: \n";
    cout << x << " before adding adding " << y << "\n";
    x += y;
    cout << x << " after adding " << y << endl;

    // End main
    return 0;
} // End main