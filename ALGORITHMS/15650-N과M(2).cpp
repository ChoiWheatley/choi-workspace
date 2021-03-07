/*
문제
자연수 N과 M이 주어졌을 때, 아래 조건을 만족하는 길이가 M인 수열을 모두 구하는 프로그램을 작성하시오.

1부터 N까지 자연수 중에서 중복 없이 M개를 고른 수열
고른 수열은 오름차순이어야 한다.
입력
첫째 줄에 자연수 N과 M이 주어진다. (1 ≤ M ≤ N ≤ 8)

출력
한 줄에 하나씩 문제의 조건을 만족하는 수열을 출력한다. 중복되는 수열을 여러 번 출력하면 안되며, 각 수열은 공백으로 구분해서 출력해야 한다.

수열은 사전 순으로 증가하는 순서로 출력해야 한다.

예제 입력 1  복사
3 1
예제 출력 1  복사
1
2
3
예제 입력 2  복사
4 2
예제 출력 2  복사
1 2
1 3
1 4
2 3
2 4
3 4
예제 입력 3  복사
4 4
예제 출력 3  복사
1 2 3 4
*/
#include<iostream>
#include<vector>
using namespace std;

void permu_ascend(bool tbl[], int idx, int selected, const int& n, const int& m);
void print_tbl(const bool (&tbl)[], int size);

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
	bool * tbl = (bool*)malloc((n+1) * sizeof(bool));
	permu_ascend(tbl, 1, 0, n, m);


	delete[] tbl;
    return 0;
}
// Binary Selection ( O/X ) function which reduce whole calculating times
// tbl[n] 	: contains n elements of selection ( O/X )
// idx		: represent this index (1 ~ n)
// selected : represent how many items are selected ( O ) (0 ~ m)
void permu_ascend(bool tbl[], int idx, int selected, const int& n, const int& m)
{
	// BASE CONDITON
	if (selected == m) {
		print_tbl((bool(&)[])(*tbl), n);
		return;
	} else if (idx > n) {
		return;
	}

	// Select 
	tbl[idx] = true;
	permu_ascend(tbl, idx+1, selected+1, n, m);

	// Don't select
	tbl[idx] = false;
	permu_ascend(tbl, idx+1, selected, n, m);
	
}
void print_tbl(const bool (&tbl)[], int size)
{
	for (int i = 0; i < size+1; i++) 
		if (tbl[i]) cout << i << ' ';
	cout << '\n';
}
