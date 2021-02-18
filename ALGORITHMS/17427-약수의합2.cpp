/*
문제
두 자연수 A와 B가 있을 때, A = BC를 만족하는 자연수 C를 A의 약수라고 한다. 예를 들어, 2의 약수는 1, 2가 있고, 24의 약수는 1, 2, 3, 4, 6, 8, 12, 24가 있다. 자연수 A의 약수의 합은 A의 모든 약수를 더한 값이고, f(A)로 표현한다. x보다 작거나 같은 모든 자연수 y의 f(y)값을 더한 값은 g(x)로 표현한다.

자연수 N이 주어졌을 때, g(N)을 구해보자.

입력
첫째 줄에 자연수 N(1 ≤ N ≤ 1,000,000)이 주어진다.

출력
첫째 줄에 g(N)를 출력한다.

예제 입력 1  복사
1
예제 출력 1  복사
1
예제 입력 2  복사
2
예제 출력 2  복사
4
예제 입력 3  복사
10
예제 출력 3  복사
87
예제 입력 4  복사
70
예제 출력 4  복사
4065
예제 입력 5  복사
10000
예제 출력 5  복사
82256014
*/
#include<iostream>
#include<cmath>
using namespace std;

typedef unsigned long long int ullint;
ullint g(int x);

int main(void)
{
    int input = 0;
    cin >> input;
    cout << g(input) << '\n';
    return 0;
}
ullint g(int x)
{
    ullint ret = 0;
    for (int i = 1; i <= x; i++){
        ret += i * int(floor(x/i));
    }
    return ret;
}
