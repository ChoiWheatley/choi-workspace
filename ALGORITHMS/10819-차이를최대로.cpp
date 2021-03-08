/*
문제
N개의 정수로 이루어진 배열 A가 주어진다. 이때, 배열에 들어있는 정수의 순서를 적절히 바꿔서 다음 식의 최댓값을 구하는 프로그램을 작성하시오.

|A[0] - A[1]| + |A[1] - A[2]| + ... + |A[N-2] - A[N-1]|

입력
첫째 줄에 N (3 ≤ N ≤ 8)이 주어진다. 둘째 줄에는 배열 A에 들어있는 정수가 주어진다. 배열에 들어있는 정수는 -100보다 크거나 같고, 100보다 작거나 같다.

출력
첫째 줄에 배열에 들어있는 수의 순서를 적절히 바꿔서 얻을 수 있는 식의 최댓값을 출력한다.

예제 입력 1  복사
6
20 1 15 8 4 10
예제 출력 1  복사
62
*/
#include<iostream>
#include<vector>
#include<climits>
#include<cmath>
#include<algorithm>
using namespace std;

int max_diff(vector<int>& seq);
int sum_diff(const vector<int>& seq);
bool next_permu(vector<int>& seq);
bool prev_permu(vector<int>& seq);
void swap(int& a, int& b);

int main(void)
{
	int n = 0;
	cin >> n;
	vector<int> seq(n);
	for (int i = 0; i < n; i++) cin >> seq[i];
	sort(seq.begin(), seq.end());
	cout << max_diff(seq) << '\n';
	return 0;
}
int sum_diff(const vector<int>& seq)
{
	int ret = 0;
	for (int i = 0; i < seq.size()-1; i++)
		ret += abs(seq[i] - seq[i+1]);
	return ret;
}
int max_diff(vector<int>& seq)
{
	int ret = INT_MIN;
	ret = max(ret, sum_diff(seq));
	// <algorithm> header 의 next_permutation() 함수는 시간초과가 발생하지 않는다.
	//while(next_permutation(seq.begin(), seq.end())) ret = max(ret, sum_diff(seq));		
	while(next_permu(seq)) {			// 왜 시간초과가 발생하지?
		ret = max(ret, sum_diff(seq));
#if DBG > 0
for (auto i : seq) cout << i << ' ';
cout << '\n';
#endif
	}
	//while(prev_permu(seq)) ret = max(ret, sum_diff(seq));
	return ret;
}
bool next_permu(vector<int>& seq)
{
	int i = 0, j = 0;
	for (i = seq.size()-1; i >= 0; i--){
		if (i == 0) return false;
		if (seq[i-1] < seq[i]) break;
	}
	for (j = i; j < seq.size()-1; j++)
		if (seq[j+1] <= seq[i-1]) break;
	swap(seq[i-1], seq[j]);
	
	for (int k = seq.size()-1; k > i; k--)
		swap(seq[i++], seq[k]);
	return true;
}
bool prev_permu(vector<int>& seq)
{
	int i = 0, j = 0;
	for (i = seq.size()-1; i >= 0; i--){
		if (i == 0) return false;
		if (seq[i-1] > seq[i]) break;
	}
	for (j = i+1; j < seq.size(); j++)
		if (seq[j+1] > seq[i-1]) break;
	swap(seq[i-1], seq[j-1]);
	
	for (int k = seq.size()-1; k > i; k--)
		swap(seq[i++], seq[k]);
	return true;
}
void swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}
