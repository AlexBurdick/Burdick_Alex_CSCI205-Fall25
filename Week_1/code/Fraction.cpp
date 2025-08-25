#include "Fraction.h"
#include <math.h>

// ------------------------------
// CONSTRUCTORS
// ------------------------------

// Constructor implementation - 2 arguments
Fraction :: Fraction(int n, int d) {
    // Make sure denominator is not negative
    if (d < 0) {
        d = abs(d);
        n = -n; // Make numerator negative instead
    }
    
    int common = gcd(abs(n), d); /**< d should not be negative at this point */
    m_num = n/common; /**< The constructor automatically reduces */
    m_den = d/common; /**< the Fraction as it is created */
}

// Constructor implementation - no argument
Fraction :: Fraction() {
    m_num = 0; /** Default to 0 */
    m_den = 1;
}


// ------------------------------
// MEMBER FUNCTIONS
// ------------------------------

// Greatest common denominator
int Fraction :: gcd(int m, int n) {
    while (m%n != 0) {
        int oldm = m;
        int oldn = n;
        m = oldn;
        n = oldm%oldn;
    }
    return n;
}

// Overloaded assigment operator
Fraction& Fraction :: operator+=(const Fraction& other) {
    *this = *this + other; /** Add the new fraction to this fraction */
    return *this;
}


// ------------------------------
// OVERLOADED OPERATORS
// ------------------------------

// Addition
Fraction operator+(const Fraction& f1, const Fraction& f2) {
    int newnum = f1.get_num()*f2.get_den() + f1.get_den()*f2.get_num();
    int newden = f1.get_den()*f2.get_den();
    return Fraction(newnum, newden);
}

// Subraction
Fraction operator-(const Fraction& f1, const Fraction& f2) {
    int new_n = f1.get_num()*f2.get_den() - f1.get_den()*f2.get_num();
    int new_d = f1.get_den()*f2.get_den();    
    return Fraction(new_n, new_d);
}

// Division
Fraction operator/(const Fraction& f1, const Fraction& f2) {
    int new_n = f1.get_num()*f2.get_den();
    int new_d = f1.get_den()*f2.get_num();    
    return Fraction(new_n, new_d);
}

/** 
 * Multiplication
 * Citation:
 * Learn C++. ©2024. 21.2 — Overloading the arithmetic operators using friend functions. LearnCpp.com.
 * https://www.learncpp.com/cpp-tutorial/overloading-the-arithmetic-operators-using-friend-functions/
 */
Fraction operator*(const Fraction& f1, const Fraction& f2) {
	return Fraction { f1.get_num()*f2.get_num(), f1.get_den()*f2.get_den() };
}