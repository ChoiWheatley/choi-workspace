#include"apss_7_big_mult_karatsuba.h"
#include"apss_7_big_mult_slow.h"

int main(void)
{
    vector<char> a, b;
    cin >> a >> b;
    cout << a << '\n' << b << '\n';

//    // test +
//    cout << "test operator+(): a+b = " << a+b << '\n';
//    // test -
//    cout << "test operator-(): a-b = " << a-b << '\n';
//    // test pow1
//    cout << "test pow10: pow10(a, 5) = " << pow10(a,5) << '\n';

    cout << karatsuba(a, b) << '\n';




    return 0;
}
