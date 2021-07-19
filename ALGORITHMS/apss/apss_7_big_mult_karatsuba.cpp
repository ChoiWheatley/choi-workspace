#include"apss_7_big_mult_karatsuba.h"
#include"apss_7_big_mult_slow.h"

int main(void)
{
    vector<int> a, b, c;
    cin >> a >> b;
    cout << a << '\n' << b << '\n';

//    // test +
//    cout << "test operator+(): a+b = " << a+b << '\n';
//    // test -
//    cout << "test operator-(): a-b = " << a-b << '\n';
//    // test pow1
//    cout << "test pow10: pow10(a, 5) = " << pow10(a,5) << '\n';

    c=karatsuba(a,b);
    for (int i = c.size()-1; i >= 0; --i)
    {
        cout << (int)c[i] << ' ';
    }
    cout << '\n';
    normalize(c);
    cout << c << '\n';





    return 0;
}
