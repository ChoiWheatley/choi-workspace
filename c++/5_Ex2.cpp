/*
 * Chapter 5 Exercise 2 
 * thie program is for error - detecting.
 * program itself calculates Celsius to Kelvin 
 * Kelvin to Celsius
 * Farenheit to Celsius and vice-versa
 * Celsius to Farenheit conversion formula : 
 * f = 1.8 * c + 32
 * Farenheit to Celsius conversion formula :
 * c = (f - 32) / 1.8
 */

#include "std_lib_facilities.h"

double ctok(double c);
double ktoc(double k);
double ftoc(double f);
double ctof(double c);

double ctok(double c)
{
    /* pre_condition : 
     * if c is below -273.15, it cannot be true
     */
    if (c < -273.15) throw runtime_error("The Temperature cannot be below '-273.15'!!!!!\n");
    // int k = c + 273.15;
    double k = c + 273.15;
    //return int;
    return k;
}
double ktoc(double k)
{
    /* pre_condition :
     * if k is lower than 0, it cannot be true
     */
    if (k < 0) throw runtime_error ("The Absolute temperature cannot be lower than 0!!!!\n");
    double c = k - 273.15;
    return c;
}
double ftoc(double f)
{
    return (1.8 * f + 32.0);
}
double ctof(double c)
{
    return ((c - 32.0) / 1.8);
}


//
//
int main()
{
    double c = 0;   // declare input valiable
    //cin >> d;       // retrieve temperature to input value
    cin >> c;
    //double k = ctok ("c");  // convert temperature
    double k = ctok(c);
    // Cout << k << '/n';      // print out temperature
    cout << "Celsius to Kelvin : " << ctok(c) << '\n';
    cout << "Kelvin to Celsius : " << ktoc(c) << '\n';
    cout << "Celsius to Farenheit : " << ctof(c) << '\n';
    cout << "Farenheit to Celsius : " << ftoc(c) << '\n';

	return 0;
}
//
//
