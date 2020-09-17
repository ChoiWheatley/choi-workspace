/*
 * a program that find all the prime number
 * such as 2, 3, 5, 7, 11, ... etc
 */

#include "std_lib_facilities.h"
#include <unistd.h>


int main()
{
    unsigned long long int num = 3;
    vector <unsigned long long int> primes = {2};
    while(1 < 2)
    {
        bool flag = true;
        num += 2;
        for (int i = 0; i < primes.size(); i++)
        {
            if (!(num % primes[i])) { flag = false; } 
        }
        if (flag)
        {
            cout << num << '\t';
            primes.push_back(num);
        }
    }
	return 0;
}
