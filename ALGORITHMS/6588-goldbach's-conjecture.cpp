/*
문제
1742년, 독일의 아마추어 수학가 크리스티안 골드바흐는 레온하르트 오일러에게 다음과 같은 추측을 제안하는 편지를 보냈다.

4보다 큰 모든 짝수는 두 홀수 소수의 합으로 나타낼 수 있다.
예를 들어 8은 3 + 5로 나타낼 수 있고, 3과 5는 모두 홀수인 소수이다. 또, 20 = 3 + 17 = 7 + 13, 42 = 5 + 37 = 11 + 31 = 13 + 29 = 19 + 23 이다.

이 추측은 아직도 해결되지 않은 문제이다.

백만 이하의 모든 짝수에 대해서, 이 추측을 검증하는 프로그램을 작성하시오.

입력
입력은 하나 또는 그 이상의 테스트 케이스로 이루어져 있다. 테스트 케이스의 개수는 100,000개를 넘지 않는다.

각 테스트 케이스는 짝수 정수 n 하나로 이루어져 있다. (6 ≤ n ≤ 1000000)

입력의 마지막 줄에는 0이 하나 주어진다.

출력
각 테스트 케이스에 대해서, n = a + b 형태로 출력한다. 이때, a와 b는 홀수 소수이다. 숫자와 연산자는 공백 하나로 구분되어져 있다. 만약, n을 만들 수 있는 방법이 여러 가지라면, b-a가 가장 큰 것을 출력한다. 또, 두 홀수 소수의 합으로 n을 나타낼 수 없는 경우에는 "Goldbach's conjecture is wrong."을 출력한다.

예제 입력 1  복사
8
20
42
0
예제 출력 1  복사
8 = 3 + 5
20 = 3 + 17
42 = 5 + 37

<TIP> Compile time initialization   // https://en.cppreference.com/w/cpp/language/constexpr
	the function body must not contain
- a goto statement
- goto label 
- case - default
- a try block
- an asm declaration (assembly)
- a definition of a variable for which initialization is performed 
- a definition of a none literal type
*/
#include<iostream>
#include<vector>
#include<string>
#include<array>
#include<cmath>
//#define DBG
#define MAX 1000000
using namespace std;

typedef unsigned long long int ull;
class BadGoldbach{ 
public:
	string what() { return "Goldbach's conjecture is wrong."; }
};
class Exit{};
// compile-time array generation
constexpr array<ull, MAX+1> init_prime(array<bool, MAX+1>& check, int& result_idx) {
	array<ull, MAX+1> result{0};
	//array<bool, MAX+1> check{false};	// erased = true
	result_idx = 0;
	for (int i = 2; i*i <= MAX; i++){
		if (check[i] == false) {
			for (int j = i+i; j <= MAX; j += i) check[j] = true;
	}	}
	// result push
	for (int i = 2; i <= MAX; i++) 
		if (check[i] == false) result[result_idx++] = i;
	return result;
}

int prime_end;
array<bool, MAX+1> check{false};
auto prime = init_prime(check, prime_end);
bool inputf(istream& is, ull& input);
void print(ull n, ull a, ull b); // n = a + b
bool verify(ull& n, ull& a);

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	try {
		ull input = 0, a = 0;
		for (; ;) {
			if (inputf(cin, input) ==  false) continue;
			if (verify(input, a)) print(input, prime[a], input-prime[a]);
			else throw BadGoldbach{};
		}
	}
	catch (BadGoldbach e){
		cout << e.what() << '\n';
		return 1;
	}
	catch (Exit e){
		return 0;
	}
	return 0;
}


bool inputf(istream& is, ull& input)
{
	is >> input;
	if (input == 0) throw Exit{};
	if (input % 2 != 0) return false;
	if (input < 5) return false;
	return is.good();
}
void print(ull n, ull a, ull b) // n = a + b
{
	cout << n << " = " << a << " + " << b << '\n';
}
bool verify(ull& n, ull& a)
// 풀이 : 두 소수 a, b 에 대해 
// a + b = n 이면
// b = n - a
// a 를 구했을 때 n-a 도 소수이면 true
{
	// 1부터 세는 이유는 [0] = 2이고, n-2 는 언제나 짝수라서
	// 세는 의미가 없다.
	for (a = 1; a < prime_end; a++)	{
		if (check[n - prime[a]] == false) return true;
	}
	return false;
}
