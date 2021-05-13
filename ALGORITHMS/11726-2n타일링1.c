/*
문제
2×n 크기의 직사각형을 1×2, 2×1 타일로 채우는 방법의 수를 구하는 프로그램을 작성하시오.

아래 그림은 2×5 크기의 직사각형을 채운 한 가지 방법의 예이다.



입력
첫째 줄에 n이 주어진다. (1 ≤ n ≤ 1,000)

출력
첫째 줄에 2×n 크기의 직사각형을 채우는 방법의 수를 10,007로 나눈 나머지를 출력한다.

예제 입력 1  복사
2
예제 출력 1  복사
2
예제 입력 2  복사
9
예제 출력 2  복사
55
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXN 1000

int tile(int n);

int main(void)
{
	int input = 0;
	scanf("%d", &input);
	printf("%d\n", tile(input));
    return 0;
}
int tile(int n)
{
	if (n == 1) return 1;
	if (n == 2) return 2;
	static int memo[MAXN+1] = {0};
	memo[1] = 1; memo[2] = 2;

	if (memo[n] > 0) return memo[n];

	memo[n] = (tile(n-1) + tile(n-2)) % 10007;

	return memo[n];
}
