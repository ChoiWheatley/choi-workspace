/*
 * a program that find all the prime number
 * such as 2, 3, 5, 7, 11, ... etc
 * using "Sieve of Eratosthenes"
 */

#include "std_lib_facilities.h"


int main()
{
    unsigned long long int max = 0;
    cout << "Please write down your max value : ";
    cin >> max;
    vector<int> siv(max + 1, 1);
    siv[0] = siv[1] = 0;
    siv[2] = 1;
    for (int i = 2; i <= max; i++)
    {
        static int cnt = 1;
        if (siv[i])
        {
            for (int j=2; j <= max/i; j++) { siv[i*j] = 0; }
            cout << i << ' ';
            if (!(cnt++ % 10)) { cout << endl; }
        }
    }
    cout << endl;
    

	return 0;
}
