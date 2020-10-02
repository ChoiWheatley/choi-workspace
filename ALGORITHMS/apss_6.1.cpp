/*
 * <재귀호출과 완전탐색>
 * reculsive function을 활용하여 1부터 N까지의
 * 수를 더하는 함수를 구현하시오.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

inline int sum(int);

int main(void)
{
    int n = 10000;
    cout << "summation among 1 to " << n << " = " << sum(n) << endl;
    return 0;
}

inline int sum(int s)
{
    // base case
    if (s == 0) return 0;
    return (s + sum(s - 1));
}