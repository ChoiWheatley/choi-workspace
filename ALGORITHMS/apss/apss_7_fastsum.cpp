/*
	AUTHOR : Choi Wheatley (chltmdgus604@naver.com)
	BRIEF : 
		이번 챕터는 분할정복 (Divide and Conquer)에 대한 내용을 다루고 있다. 
		첫 번째 예시로 1부터 n 까지 더하는 방법에 대하여 나오는데, 일반적인
		재귀호출의 방법을 사용하면 1부터 n까지 더한 값에 대한 재귀호출을 
		사용하는 방법이 있다. 하지만 분할정복을 사용하면 시간복잡도를 절반으로
		줄일 수 있게 된다.
		```
		전체 문제의 부분문제들의 크기가 모두 같기 때문이다.
		```
*/

#include <iostream>
#include <cmath>

int recur_sum(int n);
int fast_sum(int n);

int main(void)
{
	std::cout << "recur_sum(9999) = " << recur_sum(9999) << "\n";
	std::cout << "fast_sum(9999) = " << fast_sum(9999) << "\n";
	return 0;
}
int recur_sum(int n)
{
	if (n == 1) return 1;
	return n + recur_sum(n-1);
}
int fast_sum(int n)
{
	if (n == 1) return 1;
	if (n % 2 != 0) 
		return n + fast_sum(n-1);
	else
		return 2*fast_sum(n/2) + pow(n/2,2);
}
