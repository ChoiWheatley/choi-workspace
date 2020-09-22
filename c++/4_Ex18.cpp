/*
 * find a quadratic formula expression
 * input : a, b, and c
 * output : x1 and x2 or imaginary number
 */

#include "std_lib_facilities.h"
#include <complex>

inline vector<complex<double>> quadratic_formula (complex<double> a, complex<double> b, complex<double> c);

//
//
//
int main(void)
{
    complex<double> a, b, c;
    cout << "please input three values for each expression of quadratic formula. (a b c) :\n$ ";
    cin >> a >> b >> c;
    vector<complex<double>> roots;
    roots = quadratic_formula(a, b, c);
    cout << roots[0].real() << " + " << roots[0].imag() << "i\t\t"
        << roots[1].real() << " + " << roots[1].imag() << "i\n";
    return 0;
}
//
//
//
inline vector<complex<double>> quadratic_formula (complex<double> a, complex<double> b, complex<double> c)
{
    vector<complex<double>> roots;
    complex<double> d = sqrt(b*b - complex<double>{4}*a*c);
    roots.push_back( (-b + d) / (complex<double>{2} * a) );
    roots.push_back( (-b - d) / (complex<double>{2} * a) );
    return roots;
}