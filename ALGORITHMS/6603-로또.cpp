/*
독일 로또는 {1, 2, ..., 49}에서 수 6개를 고른다.

로또 번호를 선택하는데 사용되는 가장 유명한 전략은 49가지 수 중 k(k>6)개의 수를 골라 집합 S를 만든 다음 그 수만 가지고 번호를 선택하는 것이다.

예를 들어, k=8, S={1,2,3,5,8,13,21,34}인 경우 이 집합 S에서 수를 고를 수 있는 경우의 수는 총 28가지이다. ([1,2,3,5,8,13], [1,2,3,5,8,21], [1,2,3,5,8,34], [1,2,3,5,13,21], ..., [3,5,8,13,21,34])

집합 S와 k가 주어졌을 때, 수를 고르는 모든 방법을 구하는 프로그램을 작성하시오.

입력
입력은 여러 개의 테스트 케이스로 이루어져 있다. 각 테스트 케이스는 한 줄로 이루어져 있다. 첫 번째 수는 k (6 < k < 13)이고, 다음 k개 수는 집합 S에 포함되는 수이다. S의 원소는 오름차순으로 주어진다.

입력의 마지막 줄에는 0이 하나 주어진다. 

출력
각 테스트 케이스마다 수를 고르는 모든 방법을 출력한다. 이때, 사전 순으로 출력한다.

각 테스트 케이스 사이에는 빈 줄을 하나 출력한다.

예제 입력 1 
7 1 2 3 4 5 6 7
8 1 2 3 5 8 13 21 34
0
예제 출력 1 
1 2 3 4 5 6
1 2 3 4 5 7
1 2 3 4 6 7
1 2 3 5 6 7
1 2 4 5 6 7
1 3 4 5 6 7
2 3 4 5 6 7

1 2 3 5 8 13
1 2 3 5 8 21
1 2 3 5 8 34
1 2 3 5 13 21
1 2 3 5 13 34
1 2 3 5 21 34
1 2 3 8 13 21
1 2 3 8 13 34
1 2 3 8 21 34
1 2 3 13 21 34
1 2 5 8 13 21
1 2 5 8 13 34
1 2 5 8 21 34
1 2 5 13 21 34
1 2 8 13 21 34
1 3 5 8 13 21
1 3 5 8 13 34
1 3 5 8 21 34
1 3 5 13 21 34
1 3 8 13 21 34
1 5 8 13 21 34
2 3 5 8 13 21
2 3 5 8 13 34
2 3 5 8 21 34
2 3 5 13 21 34
2 3 8 13 21 34
2 5 8 13 21 34
3 5 8 13 21 34
*/
#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<stdexcept>
#include<algorithm>
using namespace std;
#define MAX_NUM 50
#define MAXK 13
#define MINK 7
#define RNGK(k) (MINK <= (k) && (k) < MAXK)
#define RNGN(n) (1 <= (n) && (n) < MAX_NUM)

void input(istream& is, int& k, int ls[MAXK]);
bool next_permu(int ls[MAXK], int k);
bool prev_permu(int ls[MAXK], int k);
void swap(int& a, int& b);
ostream& operator<< (ostream& os, int ls[MAXK]);

int main(void)
{
#if DBG > 0
	ifstream ifs{"sample.txt"};
	if(!ifs) throw runtime_error("ifs initialize error");
#endif
	for (;;)
	{
		int k = 0, ls[MAXK] = {0}, k_ls[MAXK] = {0};
#if DBG > 0
		input(ifs, k, ls);
		if (!ifs) break;
		cout << ls << '\n';
#else
		input(cin, k, ls);
		if (!cin) break;
#endif
		for (int i = 0; i < 6; i++)
			k_ls[i] = 1;
		do {
			for (int i = 0; i < k; i++)
				if (k_ls[i] == 1) cout << ls[i] << ' ';
			cout << '\n';
		} while (prev_permu(k_ls, k));
		cout << '\n';
	}
	return 0;
}
void input(istream& is, int& k, int ls[MAXK])
{
	is.clear(ios_base::goodbit);
	is >> k;
	if (!RNGK(k)) { is.clear(ios_base::failbit); return; }
	for (int i = 0; i < k; i++) {
		is >> ls[i];
		if (!RNGN(ls[i])) { is.clear(ios_base::failbit); return; }
	}
}
bool next_permu(int ls[MAXK], int k)
{
	int i = 0, j = 0;
	for (i = k-1; i > 0; i--)
		if(ls[i-1] < ls[i]) break;
	if (i == 0) return false;
	for (j = k-1; j > i; j--)
		if (ls[i-1] < ls[j]) break;
	swap(ls[i-1], ls[j]);
	for (int tmp = k-1; tmp > i; tmp--)
		swap(ls[i++], ls[tmp]);
	return true;
}
bool prev_permu(int ls[MAXK], int k)
{
	int i = 0, j = 0;
	for (i = k-1; i > 0; i--)
		if (ls[i-1] > ls[i]) break;
	if (i == 0) return false;
	for (j = k-1; j > i; j--)
		if (ls[i-1] > ls[j]) break;
	swap(ls[i-1], ls[j]);
	for (int tmp = k-1; tmp > i; tmp--)
		swap(ls[i++], ls[tmp]);
	return true;
}
void swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}
ostream& operator<< (ostream& os, int ls[MAXK])
{
	for (int i = 0; i < MAXK; i++){
		if (ls[i] == 0) break;
		os << ls[i] << ' ';
	}
	return os;
}
