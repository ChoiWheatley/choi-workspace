/*
문제
2와 5로 나누어 떨어지지 않는 정수 n(1 ≤ n ≤ 10000)가 주어졌을 때, 1로만 이루어진 n의 배수를 찾는 프로그램을 작성하시오.

입력
입력은 여러 개의 테스트 케이스로 이루어져 있다. 각 테스트 케이스는 한 줄로 이루어져 있고, n이 주어진다.

출력
1로 이루어진 n의 배수 중 가장 작은 수의 자리수를 출력한다.

예제 입력 1  
3
7
9901
예제 출력 1 
3
6
12
*/
#include<iostream>
#include<stdexcept>
#include<vector>
#include<string>
using namespace std;

int f(const int& n);
int mkn(const int& n, const int& k);

int main(void)
{
	for (int c = 0; cin >> c; cout << f(c) << '\n'){}
	return 0;
}
// m(k)%n == 0 ( m(k) >= n ) 을 만족하는 k의 최솟값 구하기
// 이때 m(k) 는 1로 이루어진 k 자리수 정수이다.
int f(const int& n)
// pre-condition : n%2!=0 && n%5!=0
{
	if ( n%2==0 || n%5==0 ) throw std::runtime_error("n is divided in 2 or 5");
	int num = 0;
	for (int k = 1; ; k++){
		// m(k)%n = (m(k-1)*10+1)%n 이라는 점을 착안
		num = num * 10 + 1;
		num %= n;
		if (num == 0) return k;
	}
	return -1;
}
// calculates m(k) % n
// = (   m(k-1)%n * 10%n + 1   ) %n
int mkn(const int& n, const int& k)
{
	if (k == 1) return 1;
	return (     mkn(n,k-1) * 10 + 1     )%n;
}
