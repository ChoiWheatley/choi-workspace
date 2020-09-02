/*
 * 자연수 n이 주어졌을 때 1부터 n까지의 합을 구하는 함수를 각각
 * 반복함수와 재귀호출로 구현해보자 
*/

#include <iostream>
using namespace std;

int sum(int n) {
    int ret = 0;
    for (int i = 0; i <= n; i++)
        ret += i;
    return ret;
}
int recur_sum(int n) {
    if (!n) return 0;
    if (n == 1) 
    {
        return 1;
    }
    return recur_sum(n - 1) + n;
}

int main() {
    int input = 100000000;
    cout << "반복함수sum : " << sum(input) << endl;
    cout << "재귀함수sum : " << recur_sum(input) << endl;

    return 0;
}