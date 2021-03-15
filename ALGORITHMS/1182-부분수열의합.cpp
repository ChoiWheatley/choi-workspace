/*
문제
N개의 정수로 이루어진 수열이 있을 때, 크기가 양수인 부분수열 중에서 그 수열의 원소를 다 더한 값이 S가 되는 경우의 수를 구하는 프로그램을 작성하시오.

입력
첫째 줄에 정수의 개수를 나타내는 N과 정수 S가 주어진다. (1 ≤ N ≤ 20, |S| ≤ 1,000,000) 둘째 줄에 N개의 정수가 빈 칸을 사이에 두고 주어진다. 주어지는 정수의 절댓값은 100,000을 넘지 않는다.

출력
첫째 줄에 합이 S가 되는 부분수열의 개수를 출력한다.

예제 입력 1 
5 0
-7 -3 -2 5 8
예제 출력 1 
1
*/
#include<iostream>
#if DBG > 0
#include<fstream>
#include<stdexcept>
#endif

#define MAXN 20
#define IST please_change_stream_object_name
using namespace std;
int selection[MAXN] = {0};

int main(void)
{
#if DBG > 0
#undef IST
#define IST ifs
	ifstream IST{"sample.txt"};
	if (!IST) throw runtime_error("file error");
#else
#undef IST
#define IST std::cin
#endif
	for (;;)
	{
		for (int i = 0; i < MAXN; i++) selection[i] = 0;
		int n = 0, s = 0, ans = 0;
		unsigned int bitwise = 0;
		IST >> n >> s;

		if (!IST) break;

		for (int i = 0; i < n; i++)
			IST >> selection[i];

		// bitwise가 1부터 시작하는 이유는 공집합 제외이기 때문.
		for (bitwise = 1; bitwise < (unsigned int)(1<<n); bitwise++){	
			int sum = 0;
			for (int idx = 0; idx < n; idx++)
				if (bitwise & (1<<idx)) sum += selection[idx];
			if (sum == s) ans++;
		}
		std::cout << ans << '\n';
	}
	return 0;
}
