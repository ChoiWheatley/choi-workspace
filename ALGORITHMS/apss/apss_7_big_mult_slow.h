#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<cmath>
#include<cstdlib>
#include<sys/types.h>

#ifndef APSS_7_BIG_MULT_SLOW_H
#define APSS_7_BIG_MULT_SLOW_H
/*
    카라츠바의 빠른 곱셈 알고리즘을 시작하기에 앞서, 
    일반적으로 곱셈을 수행하는 방식을 그대로 코드에 적용
    시켜보자.
*/

using namespace std;

vector<char> slow_mult(const vector<char>& a, const vector<char>& b);
void normalize(vector<char>& num);
//
//   int main(void)
//   {
//       vector<char> a{4,3,2,1};
//       vector<char> b{8,7,6,5};
//       vector<char> ret = slow_mult(a, b);
//       for (int i = ret.size()-1; i >= 0; --i)
//       {
//           cout << static_cast<int>(ret[i]) << ' ';
//       }
//       printf("\n");
//       return 0;
//   }
// two vectors index is equal to power of 10
// a[i] means a's i'th digit. (==a[i] * 10^i)
vector<char> slow_mult(const vector<char>& a, const vector<char>& b)
{
    vector<char> ret( a.size()+ b.size() + 1, 0 );

    // do multiply each indices
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < b.size(); j++)
        {
            ret[i+j] += a[i] * b[j];
        }
    }

    // when simple multiply is over,
    // you should NORMALIZE this, 
    // because each index might bigger than 10
    normalize(ret);

    return ret;
}
// 자릿수 올림을 처리
void normalize(vector<char>& num)
{
    num.push_back(0);
    for (int i = 0; i < num.size(); i++)
    {
        if (num[i] < 0)
        {
            char borrow = (abs(static_cast<int>(num[i])) + 9) / 10;
            num[i+1] -= borrow;
            num[i] += borrow * 10;
        }
        else
        {
            num[i+1] += num[i] / 10;
            num[i] %= 10;
        }
    }
    while(num.size() > 1 && num.back() == 0) num.pop_back();
}
#endif
