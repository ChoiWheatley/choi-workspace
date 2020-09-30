/*
 * Find a largest number of the Fibonacci series.
 * each boundary is an char, int, unsigned int, 
 * long, unsigned long, long long,
 * unsigned long long
 */

#include "std_lib_facilities.h"
#include <climits>
#include <type_traits>

template <typename T>
T find_fib();

//
//
int main()
{
    cout << "INT MAX : \t\t" << find_fib<int>() << endl;
    cout << "U_INT MAX : \t\t" << find_fib<unsigned int>() << endl;
    cout << "LONG MAX : \t\t" << find_fib<long>() << endl;
    cout << "U_LONG MAX : \t\t" << find_fib<unsigned long>() << endl;
    cout << "LONG LONG  MAX : \t" << find_fib<long long>() << endl;
    cout << "U_LONG LONG MAX : \t" << find_fib<unsigned long long>() << endl;
    return 0;
}
//
//

template <typename T>
T find_fib()
{
    vector<T> fibArr(3);
    fibArr[0] = 0;
    fibArr[1] = 1;
    while (1 < 2)
    {
        if (is_same<T, int>::value && fibArr[1] > INT_MAX - fibArr[0] ||
            is_same<T, unsigned int>::value && fibArr[1] > UINT_MAX - fibArr[0] ||
            is_same<T, long>::value && fibArr[1] > LONG_MAX - fibArr[0] ||
            is_same<T, unsigned long>::value && fibArr[1] > ULONG_MAX - fibArr[0] ||
            is_same<T, long long>::value && fibArr[1] > LONG_LONG_MAX - fibArr[0] ||
            is_same<T, unsigned long long>::value && fibArr[1] > ULONG_LONG_MAX - fibArr[0])
            return fibArr[1];
        fibArr[2] = fibArr[0] + fibArr[1];
        fibArr[0] = fibArr[1];
        fibArr[1] = fibArr[2];

        //cout << fibArr[2] << endl;
    }
}