/*
    Author : ChoiWheatley (chltmdgus604@naver.com)
    Brief  : This program counts the minimum number of make N to 1 using three methods
        1. subtract by 1
        2. divide by 3 if possible
        3. divide by 2 if possible
문제
정수 X에 사용할 수 있는 연산은 다음과 같이 세 가지 이다.

X가 3으로 나누어 떨어지면, 3으로 나눈다.
X가 2로 나누어 떨어지면, 2로 나눈다.
1을 뺀다.
정수 N이 주어졌을 때, 위와 같은 연산 세 개를 적절히 사용해서 1을 만들려고 한다. 연산을 사용하는 횟수의 최솟값을 출력하시오.

입력
첫째 줄에 1보다 크거나 같고, 106보다 작거나 같은 정수 N이 주어진다.

출력
첫째 줄에 연산을 하는 횟수의 최솟값을 출력한다.

예제 입력 1 
2
예제 출력 1 
1
예제 입력 2 
10
예제 출력 2 
3
*/
#include<stdio.h>

int f(int n);
int min(int a, int b) { if (a <= b) return a; else return b; }

#define MAXN 1000001
//int ret[MAXN] = {0};

int main(void)
{
    int n = 0;
    scanf("%d", &n);
    printf("%d\n", f(n));

    return 0;
} // int main(void)



int f(int n)
{
    int ret[MAXN] = {0};
    ret[2] = 1;
    ret[3] = 1;

    if ( n <= 3 ) return ret[n];
    for ( int i = 4; i <= n; i++){
        ret[i] = 1 + ret[i-1];
        if ( i % 2 == 0 )
            ret[i] = min(ret[i], 1 + ret[i/2]);
        if ( i % 3 == 0 )
            ret[i] = min(ret[i], 1 + ret[i/3]);
    }

    return ret[n];
}
