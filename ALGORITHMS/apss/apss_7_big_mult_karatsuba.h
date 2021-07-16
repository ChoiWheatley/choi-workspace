#include"apss_7_big_mult_slow.h"

#ifndef BIG_MULT_KARATSUBA_H
#define BIG_MULT_KARATSUBA_H

using namespace std;

extern void normalize(vector<char>& num);
extern vector<char> slow_mult(const vector<char>& a, const vector<char>& b);

vector<char> karatsuba(vector<char>& a, vector<char>& b);
// helper functions
vector<char> operator+(const vector<char>& a, const vector<char>& b);
vector<char> operator-(const vector<char>& a, const vector<char>& b);
vector<char> pow10(const vector<char>& a, int amt);
istream& operator>>(istream& ist, vector<char>& a);
ostream& operator<<(ostream& os, const vector<char>& a);

vector<char> karatsuba(vector<char>& a, vector<char>& b)
{
    int an = a.size(), bn = b.size();
    if (an < bn) 
        return karatsuba(b, a);
    // base condition : a 또는 b가 비어있는 경우
    if (an == 0 || bn == 0) 
        return vector<char>();
    // base condition : a 가 비교적 짧은 경우, 일반 mult로 해결한다.
    if (bn < 5) 
        return slow_mult(a, b);

    // a, b를 half 자리와 그 나머지로 분리한다.
    int half = an / 2;
    vector<char> a0 {a.begin(), a.begin()+half};
    vector<char> a1 {a.begin()+half, a.end()};
    vector<char> b0 {b.begin(), b.begin() + min(b.size(), (size_t)half)};
    vector<char> b1 {b.begin() + min(b.size(), (size_t)half), b.end()};

//    cerr << "a0=" << a0 << ", a1=" << a1 << '\n';
//    cerr << "b0=" << b0 << ", b1=" << b1 << '\n';

    // a * b == z0 + z1*pow(10,half) + z2*pow(10, half+half) 이때,
    // z0 = a0 * b0
    // z2 = a1 * b1
    // z1 = (a1*b0 + a0*b1) OR ( (a0+a1)*(b0+b1) - z0 - z2 )
    vector<char> z0 = karatsuba(a0, b0);
    vector<char> z2 = karatsuba(a1, b1);

    a0 = a0 + a1;
    b0 = b0 + b1;
    vector<char> z1 = karatsuba(a0, b0) - z0 - z2;
    z1 = pow10(z1, half);
    z2 = pow10(z2, half+half);

    vector<char> ret(0);
    ret = ret + z0 + z1 + z2;
    return ret;
}
vector<char> operator+(const vector<char>& a, const vector<char>& b)
{
    int an = a.size(), bn = b.size();
    if (an < bn) return operator+(b, a);

    vector<char> ret(a);
    for (int i = 0; i < bn; i++)
    {
        ret[i] += b[i];
    }

    normalize(ret);
    return ret;
}
vector<char> operator-(const vector<char>& a, const vector<char>& b)
{
    int an = a.size(), bn = b.size();
    if (an < bn) return operator-(b, a);

    vector<char> ret(a);
    for (int i = 0; i < bn; i++)
    {
        ret[i] -= b[i];
    }
    
    normalize(ret);
    return ret;
}
vector<char> pow10(const vector<char>& a, int amt)
{
    vector<char> ret{a};
    ret.insert(ret.begin(), amt, 0);
    return ret;
}
// "1234567890" -> [0,9,8,7,6,5,4,3,2,1]
istream& operator>>(istream& ist, vector<char>& a)
{
    char c;
    while ((c = ist.get()))
    {
        if (c == '\n') break;
        a.insert(a.begin(), atoi(&c));
    }
    return ist;
}
// [0,9,8,7,6,5,4,3,2,1] -> "1234567890"
ostream& operator<<(ostream& os, const vector<char>& a)
{
    for (int i = a.size()-1; i >= 0; --i)
    {
        os << (int)a[i] ;
    }
    return os;
}
#endif
