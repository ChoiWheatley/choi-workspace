/*
문제
크기가 N×M인 격자판의 각 칸에 정수가 하나씩 들어있다. 이 격자판에서 칸 K개를 선택할 것이고, 선택한 칸에 들어있는 수를 모두 더한 값의 최댓값을 구하려고 한다. 단, 선택한 두 칸이 인접하면 안된다. r행 c열에 있는 칸을 (r, c)라고 했을 때, (r-1, c), (r+1, c), (r, c-1), (r, c+1)에 있는 칸이 인접한 칸이다.

입력
첫째 줄에 N, M, K가 주어진다. 둘째 줄부터 N개의 줄에 격자판에 들어있는 수가 주어진다.

출력
선택한 칸에 들어있는 수를 모두 더한 값의 최댓값을 출력한다.

제한
1 ≤ N, M ≤ 10
1 ≤ K ≤ min(4, N×M)
격자판에 들어있는 수는 -10,000보다 크거나 같고, 10,000보다 작거나 같은 정수이다.
항상 K개의 칸을 선택할 수 있는 경우만 입력으로 주어진다.
예제 입력 1  복사
1 1 1
1
예제 출력 1  복사
1
예제 입력 2  복사
2 2 2
1 2
3 4
예제 출력 2  복사
5
예제 입력 3  복사
2 2 2
5 4
4 5
예제 출력 3  복사
10
예제 입력 4  복사
5 5 3
1 9 8 -2 0
-1 9 8 -3 0
-5 1 9 -1 0
0 0 0 9 8
9 9 9 0 0
예제 출력 4  복사
27
*/
#include<iostream>
#include<fstream>	// for debugging
#include<vector>
#include<climits>
#include<iomanip>	// to use ios_base::setw()
#include<unistd.h>	// to use sleep()
using namespace std;

#define DBG 1
#define MAX 10

const vector<int> di{0, 1, 0, -1};
const vector<int> dj{1, 0, -1, 0};
bool selected[MAX][MAX];

vector<vector<int>> init_board(istream& is, int& n, int& m, int& k);
int nmk(const vector<vector<int>>& board, int k, int sum = 0, int start_i = 0, int start_j = 0);
ostream& operator<<(ostream& os, const vector<vector<int>>& board);
bool is_adjacent(int i, int j);

int main(void)
{
	int n, m, k;
#ifdef DBG
	fstream fst{"sample.txt"};
	if (!fst) throw runtime_error("filestream error");
	for (;fst;){
		vector<vector<int>> board = init_board(fst, n, m, k);
		cout << board;
		cout << nmk(board, k, 0) << '\n';

	}
	#else
	vector<vector<int>> board = init_board(cin, n, m, k);
	cout << nmk(board, k) << '\n';
#endif
	return 0;
}
vector<vector<int>> init_board(istream& is, int& n, int& m, int& k)
{
	is >> n >> m >> k;
	vector<vector<int>> ret(n, vector<int>(m, INT_MIN));
	int tmp = 0;
	if (k > n*m) throw runtime_error("k is bigger than n * m");
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			is >> tmp;
			ret[i][j] = tmp;
		}
	}
	return ret;
}
int nmk(const vector<vector<int>>& board, int k, int sum, int start_i, int start_j)
{
	// BASE CONDITION
	if (k < 1) return sum;
	if (k > 4) k = 4;

	int summax = INT_MIN;			// 찾는데 힘들었다 벌레친구 ^___^;;;;

	// [start_i+1 ~ n][0 ~ m]
	for (int i = start_i; i < board.size(); i++){
		for (int j = (i == start_i ? start_j : 0);   
				j < board[0].size();   
				j++
			){
			if (selected[i][j] || is_adjacent(i,j)) continue;

			selected[i][j] = true;
			sum += board[i][j];
			k--;

			summax = max(summax, nmk(board, k, sum, i, j));

			// return back
			selected[i][j] = false;
			sum -= board[i][j];
			k++;
		}
	}
	return summax;
}
ostream& operator<<(ostream& os, const vector<vector<int>>& board)
{
	for (auto i : board){
		for (auto j : i)
			os << setw(5) << j << ' ';
		os << '\n';
	}
	return os;
}
bool is_adjacent(int i, int j)
{
	for (int d = 0; d < di.size(); d++){
		int ni = i + di[d];
		int nj = j + dj[d];
		if (selected[ni][nj]) return true;
	}
	return false;
}
