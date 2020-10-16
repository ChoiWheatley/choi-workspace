/*
 * Chapter 6 Exercise 10 Permutation and Combination calculator program
 * Design, Pseudo code, Implement
# Design
     - Program asks users two numbers
     - program asks whether they want to calculate P or C
     - program prints out the result.
 
# pseudo code
< Greetings and input two numbers and choose P or C >
cout << "Hello, please write two numbers below\n"
cin >> a >> b
cout << "Please write 'P' or 'C' as Permutation and Combination"
cin >> p_or_c;

# Permutation and Combination Parts
< Permutation (a , b) >
if (a < b) error "a should not be bigger than b"
if (a == 0) return 1
return product( a-b+1, a )

< Combination (a , b) >
return Permutation (a , b) / product (1 , b)

< product (n , m) >
ret = 1
for i is n to m
    ret = ret * i
return ret

 * 
 */

#include "std_lib_facilities.h"

typedef unsigned long long int ullint;

ullint permutation (ullint, ullint);
ullint combination (ullint, ullint);
ullint product (ullint, ullint);

//
//
int main()
{
    try
    {
        ullint a = 0, b = 0;
        char p_or_c = 0;
        cout << "Hello, please write two numbers below\n$ ";
        cin >> a >> b;
        cout << "Please input P or C as Permutation and Combination\n$ " ; 
        cin >> p_or_c;
        if (p_or_c == 'P' || p_or_c == 'p')
            cout << "P(" << a << ", " << b << ") = " << permutation(a, b) << endl;
        else if (p_or_c == 'C' || p_or_c == 'c')
            cout << "C(" << a << ", " << b << ") = " << combination(a, b) << endl;
        else error("wrong input value. Please write P or p or C or c\n");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch (...)
    {
        cerr << "I cannot find any specific error\n";
    }
    return 0;
}
//
//

ullint permutation (ullint a, ullint b){
    if (a < b) error ("ERROR (permutation()) : rvalue should not bigger than lvalue\n");
    if (a == 0) return 1;
    return product (a-b+1, a);
}
ullint combination (ullint a, ullint b){
    return permutation (a, b) / (product(1, b));
}
ullint product (ullint n, ullint m){
    if (n > m) error ("ERROR (product()) : lvalue should not bigger than rvalue\n");
    ullint ret = 1;
    for (ullint i = n; i < m; i++)
    {
        if (ret > UINT64_MAX / i) error ("ERROR (product()) : return value is too big (Unsigned int 64 bit)\n");
        ret *= i;
    }
    return ret;
}