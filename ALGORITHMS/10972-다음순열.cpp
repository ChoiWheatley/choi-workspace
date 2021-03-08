/*
문제
1부터 N까지의 수로 이루어진 순열이 있다. 이때, 사전순으로 다음에 오는 순열을 구하는 프로그램을 작성하시오.

사전 순으로 가장 앞서는 순열은 오름차순으로 이루어진 순열이고, 가장 마지막에 오는 순열은 내림차순으로 이루어진 순열이다.

N = 3인 경우에 사전순으로 순열을 나열하면 다음과 같다.

1, 2, 3
1, 3, 2
2, 1, 3
2, 3, 1
3, 1, 2
3, 2, 1
입력
첫째 줄에 N(1 ≤ N ≤ 10,000)이 주어진다. 둘째 줄에 순열이 주어진다.

출력
첫째 줄에 입력으로 주어진 순열의 다음에 오는 순열을 출력한다. 만약, 사전순으로 마지막에 오는 순열인 경우에는 -1을 출력한다.

예제 입력 1  복사
4
1 2 3 4
예제 출력 1  복사
1 2 4 3
예제 입력 2  복사
5
5 4 3 2 1
예제 출력 2  복사
-1
*/
#include<iostream>
#include<vector>

// return value : is this sequence 'not' a last sequence?
bool next_permutation(std::vector<int>& sequence);
void swap(int& a, int& b);

int main(void)
{
	std::vector<int> seq;
	int n = 0, input = 0;
	std::cin >> n;
	for (;n>0; n--){
		std::cin >> input;
		seq.push_back(input);
	}
	if (!next_permutation(seq)) {std::cout << -1 << '\n'; return 0;}
	for(auto i : seq) std::cout << i << ' ';
	std::cout << '\n';
	return 0;
}
// return value : is this sequence 'not' a last sequence?
bool next_permutation(std::vector<int>& sequence)
{
	int i = 0, j = 0;
	for (i = sequence.size()-1; i >= 0; i--){
		if (i == 0) return false;		// 전체순열의 마지막 번째
		if (sequence[i-1] < sequence[i]) break;
	}
	// 내림차순의 순열에서 바꿀 수보다 작다는 건 곧 그 이전수가 된다.
	for (j = i; j < sequence.size()-1; j++)
		if (sequence[j+1] < sequence[i-1]) break;
	swap(sequence[i-1], sequence[j]);
	for (int k = sequence.size()-1; k > i; k--)
		swap(sequence[i++], sequence[k]);
	return true;
}
void swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}
