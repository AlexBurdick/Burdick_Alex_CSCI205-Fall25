#include "Fraction.h"
#include <math.h>
#include <string>

// ------------------------------
// CONSTRUCTORS
// ------------------------------

// Constructor implementation - no argument
Fraction :: Fraction()
{
    m_numerator = 0; /**< Default to 0 */
    m_denominator = 1;
}

// Constructor implementation - 2 arguments
Fraction :: Fraction(int n, int d)
{
    m_numerator = n;
    m_denominator = d;
    this->simplify();
}


// ------------------------------
// MEMBER FUNCTIONS
// ------------------------------

// Greatest common denominator
int Fraction :: gcd(int m, int n)
{
    while (m%n != 0)
    {
        int oldm = m;
        int oldn = n;
        m = oldn;
        n = oldm % oldn;
    }

    return n;
}


// Overloaded operators:
// Addition
Fraction Fraction :: operator+(const Fraction& other) const
{
    int new_n = m_numerator*other.m_denominator + m_denominator*other.m_numerator;
    int new_d = m_denominator*other.m_denominator;
    return Fraction(new_n, new_d);
}

// Subraction
Fraction Fraction :: operator-(const Fraction& other) const
{
    int new_n = m_numerator*other.m_denominator - m_denominator*other.m_numerator;
    int new_d = m_denominator*other.m_denominator;
    return Fraction(new_n, new_d);
}

// Division
Fraction Fraction :: operator/(const Fraction& other) const
{
    int new_n = m_numerator*other.m_denominator;
    int new_d = m_denominator*other.m_numerator;
    return Fraction(new_n, new_d);
}

// Multiplication
Fraction Fraction :: operator*(const Fraction& other) const
{
	return Fraction(m_numerator*other.m_numerator, 
                    m_denominator*other.m_denominator);
}

// Assignment operator
Fraction Fraction :: operator+=(const Fraction& other)
{
    *this = *this + other;
    return *this;
}

// Output operator
std::ostream& operator<< (std::ostream& out_stream, const Fraction& f)
{
    if (f.m_numerator > f.m_denominator) // Convert to mixed fraction
    {
        int i = f.m_numerator / f.m_denominator;
        int r = f.m_numerator % f.m_denominator;
        std::string output = std::to_string(i) + " " + std::to_string(r) + 
                             "/" + std::to_string(f.m_denominator);
        out_stream << output;
	    return out_stream;
    }
    
    // Put into stream
    std::string output = std::to_string(f.m_numerator) + "/" + std::to_string(f.m_denominator);
    out_stream << output;
	return out_stream;
}