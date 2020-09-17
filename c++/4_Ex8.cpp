/*
 * calculate each iteration of doubling numbers
 * and also find out how many iterations are required
 * at least 1000 / 1,000,000 / 1,000,000,000
 */

#include "std_lib_facilities.h"
#include <unistd.h>


int main()
{
    constexpr long long int thousand = 1000;
    constexpr long long int million = 10000000;
    constexpr long long int billion = 1000000000;
    unsigned long long int now = 2, term = 0, prev;
    while (1 < 2)
    {
        cout << now << '\n';
        prev = now;
        now *= 2;
        term++;
        if (now > thousand && prev < thousand)
        { cout << '\n' << term << "th square reached out thousand!\n"; }
        else if (now > million && prev < million)
        { cout << '\n' <<  term << "th square reached out million!\n"; }
        else if (now > billion && prev < billion)
        { cout << '\n' <<  term << "th square reached out billion!\n"; }

        if (now == 0)
        {
            break;
        }
        usleep(9000);
    }
    cout << prev * 2 - 1 << endl;
    return 0;
}

