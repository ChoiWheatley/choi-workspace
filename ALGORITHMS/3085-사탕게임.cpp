/*

<<< Optimized Version >>>
두 칸만 서로 바꾸는 거라면... 영향받는 행과 열은 오직 3줄 뿐이다.


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
#define RIGHT 0
#define DOWN 1
using namespace std;

//#define DBG

int n = 0;
// right, down
const int dx[] = { 1, 0 };
const int dy[] = { 0, 1 };

int longest_length(const vector<string>& board, int y, int x, int y_, int x_);
/* helper functions */
void input(istream& is, vector<string>& board);
ostream& operator<<(ostream& os, vector<string>& board);
bool is_bound(const vector<string>& board, int y, int x);

int main(int argc, char ** argv)
{
	vector<string> board;	// (N+2) * (N+2) board with boundary
#ifdef DBG
	ifstream ifs{"sample.txt"};
	if(!ifs) runtime_error("file wrong");
	input(ifs, board);
#else
	input(cin, board);
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
					max_length = max(max_length, longest_length(board, y, x, y_, x_));
					swap(board[y][x], board[y_][x_]);		// 원상복귀
				}
			}
		}
	}
	cout << max_length << '\n';

	return 0;
}
int longest_length(const vector<string>& board, int y, int x, int y_, int x_)
{
	int max_length = 0;
	int cnt = 1;
	int fixed_x[2] = {x, x_};
	int fixed_y[2] = {y, y_};

// horizontal
	for (int i = 0; i < 2; i++) {
		cnt = 1;
		for (int j = 1; j < n; j++){
			if (board[fixed_y[i]][j] == board[fixed_y[i]][j+1]) cnt++;
			else cnt = 1;
			max_length = max(max_length, cnt);
		}
	}
// vertical
	for (int i = 0; i < 2; i++) {
		cnt = 1;
		for (int j = 1; j < n; j++){
			if (board[j][fixed_x[i]] == board[j+1][fixed_x[i]]) cnt++;
			else cnt = 1;
			max_length = max(max_length, cnt);
		}
	}
	return max_length;
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
