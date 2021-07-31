#include"7_big_mult_slow.h"
#include"7_big_mult_karatsuba.h"

int main(void)
{
    vector<int> a, b, c;
    cin >> a >> b;
    cout << a << ", " << b << '\n';
    c=slow_mult(a,b);
    for(int i = c.size()-1; i >= 0; --i)
    {
        cout << (int)c[i] << ' ';
    }
    cout << '\n';
    normalize(c);
    cout << c << '\n';

    return 0;
}
