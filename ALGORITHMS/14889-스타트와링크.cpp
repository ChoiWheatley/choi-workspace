/*
문제
오늘은 스타트링크에 다니는 사람들이 모여서 축구를 해보려고 한다. 축구는 평일 오후에 하고 의무 참석도 아니다. 축구를 하기 위해 모인 사람은 총 N명이고 신기하게도 N은 짝수이다. 이제 N/2명으로 이루어진 스타트 팀과 링크 팀으로 사람들을 나눠야 한다.

BOJ를 운영하는 회사 답게 사람에게 번호를 1부터 N까지로 배정했고, 아래와 같은 능력치를 조사했다. 능력치 Sij는 i번 사람과 j번 사람이 같은 팀에 속했을 때, 팀에 더해지는 능력치이다. 팀의 능력치는 팀에 속한 모든 쌍의 능력치 Sij의 합이다. Sij는 Sji와 다를 수도 있으며, i번 사람과 j번 사람이 같은 팀에 속했을 때, 팀에 더해지는 능력치는 Sij와 Sji이다.

N=4이고, S가 아래와 같은 경우를 살펴보자.

i\j	1	2	3	4
1	 	1	2	3
2	4	 	5	6
3	7	1	 	2
4	3	4	5	 
예를 들어, 1, 2번이 스타트 팀, 3, 4번이 링크 팀에 속한 경우에 두 팀의 능력치는 아래와 같다.

스타트 팀: S12 + S21 = 1 + 4 = 5
링크 팀: S34 + S43 = 2 + 5 = 7
1, 3번이 스타트 팀, 2, 4번이 링크 팀에 속하면, 두 팀의 능력치는 아래와 같다.

스타트 팀: S13 + S31 = 2 + 7 = 9
링크 팀: S24 + S42 = 6 + 4 = 10
축구를 재미있게 하기 위해서 스타트 팀의 능력치와 링크 팀의 능력치의 차이를 최소로 하려고 한다. 위의 예제와 같은 경우에는 1, 4번이 스타트 팀, 2, 3번 팀이 링크 팀에 속하면 스타트 팀의 능력치는 6, 링크 팀의 능력치는 6이 되어서 차이가 0이 되고 이 값이 최소이다.

입력
첫째 줄에 N(4 ≤ N ≤ 20, N은 짝수)이 주어진다. 둘째 줄부터 N개의 줄에 S가 주어진다. 각 줄은 N개의 수로 이루어져 있고, i번 줄의 j번째 수는 Sij 이다. Sii는 항상 0이고, 나머지 Sij는 1보다 크거나 같고, 100보다 작거나 같은 정수이다.

출력
첫째 줄에 스타트 팀과 링크 팀의 능력치의 차이의 최솟값을 출력한다.

예제 입력 1  복사
4
0 1 2 3
4 0 5 6
7 1 0 2
3 4 5 0
예제 출력 1  복사
0
예제 입력 2  복사
6
0 1 2 3 4 5
1 0 2 3 4 5
1 2 0 3 4 5
1 2 3 0 4 5
1 2 3 4 0 5
1 2 3 4 5 0
예제 출력 2  복사
2
예제 입력 3  복사
8
0 5 4 5 4 5 4 5
4 0 5 1 2 3 4 5
9 8 0 1 2 3 1 2
9 9 9 0 9 9 9 9
1 1 1 1 0 1 1 1
8 7 6 5 4 0 3 2
9 1 9 1 9 1 0 9
6 5 4 3 2 1 9 0
예제 출력 3  복사
1
힌트
예제 2의 경우에 (1, 3, 6), (2, 4, 5)로 팀을 나누면 되고, 예제 3의 경우에는 (1, 2, 4, 5), (3, 6, 7, 8)로 팀을 나누면 된다.
*/
#include<iostream>
#include<fstream>
#include<vector>
#include<stdexcept>
#include<climits>
#include<cmath>
using namespace std;

#define NMAX 20

int N = 0;
int synergy(const vector<vector<int>>& player, const vector<int>& indices);
int team_balance(const vector<vector<int>>& player, int idx = 0, vector<int> team_start = vector<int>{}, vector<int> team_link = vector<int>{});
vector<vector<int>> input(istream& is);
ostream& operator<< (ostream& os, const vector<vector<int>>& mat);
ostream& operator<< (ostream& os, const vector<int>& ls);

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	vector<vector<int>> player;
#ifdef DBG
	ifstream ifs{"sample.txt"};
	if(!ifs) throw runtime_error("text file cannot open");
	for (;;){
		player = input(ifs);
		if (!ifs) return 2;
		cout << "next\n" << player;
		cout << team_balance(player) << '\n';
	}
#else
	player = input(cin);
	cout << team_balance(player) << '\n';
#endif
	return 0;
}
int synergy(const vector<vector<int>>& player, const vector<int>& indices)
{
	int ret = 0;
	for (auto i : indices){
		for (auto j : indices){
			if (i == j) continue;
			ret += player[i][j];
		}
	}
	return ret;
}
int team_balance(const vector<vector<int>>& player, int idx, vector<int> team_start, vector<int> team_link)
{
	//BASECONDITION
	if (idx == N) {
		if (team_start.size() != team_link.size()) return INT_MAX;
#if DBG > 1
		cout << "team_start = \n" << team_start;
		cout << "team_link = \n" << team_link;
		cout << "====== " << synergy(player, team_start) << "-" << synergy(player, team_link) << " ===== ";
		cout << abs(synergy(player, team_start) - synergy(player, team_link)) << "\n\n";
#endif
		return abs(synergy(player, team_start) - synergy(player, team_link));
	}
	//UNNECESSARY CONDITION : Backtraking Method
	if (team_start.size() > N/2 || 
		team_link.size() > N/2) return INT_MAX;

	int min_gap = INT_MAX;
	// idx -> team_start
	team_start.push_back(idx);
	min_gap = min(min_gap, team_balance(player, idx+1, team_start, team_link));
	team_start.pop_back();
	// idx -> team_link
	team_link.push_back(idx);
	min_gap = min(min_gap, team_balance(player, idx+1, team_start, team_link));
	team_link.pop_back();

	return min_gap;
}
vector<vector<int>> input(istream& is)
{
	N = 0;
	is >> N;
	vector<vector<int>> ret(N, vector<int>(N));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			is >> ret[i][j];
	return ret;
}
ostream& operator<< (ostream& os, const vector<vector<int>>& mat)
{
	for (auto i : mat){
		for (auto j : i)
			os << j << ' ';
		os << '\n';
	}
	return os;
}

ostream& operator<< (ostream& os, const vector<int>& ls)
{
	for (auto i : ls)
		os << i << ' ';
	os << '\n';
	return os;
}
