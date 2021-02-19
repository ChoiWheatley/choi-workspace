/*
문제
상근이는 어렸을 적에 "봄보니 (Bomboni)" 게임을 즐겨했다.

가장 처음에 N×N크기에 사탕을 채워 놓는다. 사탕의 색은 모두 같지 않을 수도 있다. 상근이는 사탕의 색이 다른 인접한 두 칸을 고른다. 그 다음 고른 칸에 들어있는 사탕을 서로 교환한다. 이제, 모두 같은 색으로 이루어져 있는 가장 긴 연속 부분(행 또는 열)을 고른 다음 그 사탕을 모두 먹는다.

사탕이 채워진 상태가 주어졌을 때, 상근이가 먹을 수 있는 사탕의 최대 개수를 구하는 프로그램을 작성하시오.

입력
첫째 줄에 보드의 크기 N이 주어진다. (3 ≤ N ≤ 50)

다음 N개 줄에는 보드에 채워져 있는 사탕의 색상이 주어진다. 빨간색은 C, 파란색은 P, 초록색은 Z, 노란색은 Y로 주어진다.

사탕의 색이 다른 인접한 두 칸이 존재하는 입력만 주어진다.

출력
첫째 줄에 상근이가 먹을 수 있는 사탕의 최대 개수를 출력한다.

예제 입력 1  복사
5
YCPZY
CYZZP
CCPPP
YCYZC
CPPZZ
예제 출력 1  복사
4
*/
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<stdexcept>
#include<unistd.h>	// to use sleep() function
#define BOUND '0'
using namespace std;
#define DBG 1

int n = 0;

int longest_length(vector<string> board);
int adjacent(vector<string>& board, int y, int x);
/* helper functions */
void input(istream& is, vector<string>& board);
ostream& operator<<(ostream& os, vector<string>& board);
bool is_bound(const vector<string>& board, int y, int x);

int main(void)
{
	vector<string> board;	// (N+2) * (N+2) board with boundary
	// 오른쪽, 아래하고만 교환하면 모든 칸에 대해 검사하게 된다.
	const static int dx[2] = { 1, 0 };
	const static int dy[2] = { 0, 1 };
	ifstream ifs{"sample.txt"};
	if(!ifs) runtime_error("file wrong");
	input(ifs, board);
#ifdef DBG
cerr << board << '\n';
#endif
	
	// TODO
	int max_length = 1;
	for (int y = 1; y < n+1; y++){
		for (int x = 1; x < n+1; x++){
			for (int i = 0; i < 2; i++){
				int x_ = x + dx[i];
				int y_ = y + dy[i];
				if (!is_bound(board, y_, x_)) {
					swap(board[y][x], board[y_][x_]);
					max_length = max(max_length, longest_length(board));
					swap(board[y][x], board[y_][x_]);
				}
			}
		}
	}
	cout << max_length << '\n';

	return 0;
}
int longest_length(vector<string> board)
// BASE CONDITION : 4 방향 모두 막혔을 때
{
	int max_length = 0;

	for (int y = 1; y < n+1; y++){
		for (int x = 1; x < n+1; x++){
#ifdef DBG
cerr << board << '\n';
sleep(1);
#endif
			max_length = max(max_length, adjacent(board, y, x));
		}
	}
	return max_length;
}
// adjacent function ERASES when visit
int adjacent(vector<string>& board, int y, int x)
{
	// 상, 우, 하, 좌
	const static int dx[4] = { 0, 1, 0, -1 };
	const static int dy[4] = { -1, 0, 1, 0 };
// BASE CONDITION : board[i][j] is boundary
	if (is_bound(board, y, x)) return 0;

	int cnt = 1;
	char sample = board[y][x];
	board[y][x] = BOUND;	// prevent from re-visiting
	for (int d = 0; d < 4; d++){
		int y_ = y + dy[d];
		int x_ = x + dx[d];
		if (sample == board[y_][x_]){
			cnt += adjacent(board, y_, x_);
		}
	}
	return cnt;
}
void input(istream& is, vector<string>& board)
{
	is >> n;
	//init
	for (int i = 0; i < n+2; i++)
		board.push_back(string(n+2, BOUND));
	//
	for (int i = 1; i < n+1; i++){
		is.ignore(100, '\n');
		for (int j = 1; j < n+1; j++){
			board[i][j] = is.get();
	}	}
}
ostream& operator<<(ostream& os, vector<string>& board)
{
	for (auto i : board)
		os << i << '\n';
	return os;
}
bool is_bound(const vector<string>& board, int y, int x)
{
	if (y < 1 || n < y ||
		x < 1 || n < x ||
		board[y][x] == BOUND) return true;
	return false;
}
