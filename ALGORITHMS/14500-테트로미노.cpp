/*
문제
폴리오미노란 크기가 1×1인 정사각형을 여러 개 이어서 붙인 도형이며, 다음과 같은 조건을 만족해야 한다.

정사각형은 서로 겹치면 안 된다.
도형은 모두 연결되어 있어야 한다.
정사각형의 변끼리 연결되어 있어야 한다. 즉, 꼭짓점과 꼭짓점만 맞닿아 있으면 안 된다.
정사각형 4개를 이어 붙인 폴리오미노는 테트로미노라고 하며, 다음과 같은 5가지가 있다.

[][][][]

[][]
[][]

[]
[]
[][]

[]
[][]
  []

[][][]
  []

아름이는 크기가 N×M인 종이 위에 테트로미노 하나를 놓으려고 한다. 종이는 1×1 크기의 칸으로 나누어져 있으며, 각각의 칸에는 정수가 하나 쓰여 있다.

테트로미노 하나를 적절히 놓아서 테트로미노가 놓인 칸에 쓰여 있는 수들의 합을 최대로 하는 프로그램을 작성하시오.

테트로미노는 반드시 한 정사각형이 정확히 하나의 칸을 포함하도록 놓아야 하며, 회전이나 대칭을 시켜도 된다.

입력
첫째 줄에 종이의 세로 크기 N과 가로 크기 M이 주어진다. (4 ≤ N, M ≤ 500)

둘째 줄부터 N개의 줄에 종이에 쓰여 있는 수가 주어진다. i번째 줄의 j번째 수는 위에서부터 i번째 칸, 왼쪽에서부터 j번째 칸에 쓰여 있는 수이다. 입력으로 주어지는 수는 1,000을 넘지 않는 자연수이다.

출력
첫째 줄에 테트로미노가 놓인 칸에 쓰인 수들의 합의 최댓값을 출력한다.

예제 입력 1 
5 5
1 2 3 4 5
5 4 3 2 1
2 3 4 5 6
6 5 4 3 2
1 2 1 2 1
예제 출력 1 
19
예제 입력 2 
4 5
1 2 3 4 5
1 2 3 4 5
1 2 3 4 5
1 2 3 4 5
예제 출력 2 
20
예제 입력 3 
4 10
1 2 1 2 1 2 1 2 1 2
2 1 2 1 2 1 2 1 2 1
1 2 1 2 1 2 1 2 1 2
2 1 2 1 2 1 2 1 2 1
예제 출력 3 
7
*/
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

//#define DBG

// 0, 0 don't need to be explicit
// even ones are y, odd ones are x indices
const vector<vector<int>> tetromino{
    {0, 1, 0, 2, 0, 3},
    {0, 1, 1, 0, 1, 1},
    {1, 0, 2, 0, 2, 1},
    {1, 0, 1, 1, 2, 1},
	{1, 0, 1, 1, 2, 0}
};

int score(const vector<vector<int>>& board, const vector<int> tet, int y, int x);
void rotate(vector<vector<int>>& board);
void flip_hori(vector<vector<int>>& board);
/* helper functions */
void input(istream& is, vector<vector<int>>& board);
ostream& operator<<(ostream& os, const vector<vector<int>>& board);

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<vector<int>> board;
    int max_score = 0;
#ifdef DBG
    ifstream ifs{"sample.txt"};
    if(!ifs) return 1;
    input(ifs, board);
    cout << board << '\n';
#else
    input(cin, board);
#endif

    // Do 4 rotate(). Do 1 flip_hori() for each rotate()
	for (auto tet : tetromino){
		for (int rotation = 0; rotation < 4; rotation++){
			for (int flipping = 0; flipping < 2; flipping++){
				for (int y = 0; y < board.size(); y++)
					for (int x = 0; x < board[0].size(); x++)
						max_score = max(max_score, score(board, tet, y, x));
				flip_hori(board);
			}
			rotate(board);
		}
	}
    cout << max_score << '\n';

    return 0;
}
int score(const vector<vector<int>>& board, const vector<int> tet, int y, int x)
{
    vector<int> dx{0};
    vector<int> dy{0};
    int ret = 0;
    for (int i = 0; i < tet.size(); i++)
        (i%2==0) ? dx.push_back(tet[i]) : dy.push_back(tet[i]);
// base condition : out of boundary
    for (auto i : dx) if (board[0].size() <= x+i) return 0; 
    for (auto i : dy) if (board.size() <= y+i) return 0; 
    
    for (int i = 0; i < dx.size(); i++){
        ret += board[y+dy[i]][x+dx[i]];
#ifdef DBG
		cerr << board[y+dy[i]][x+dx[i]] << ',';
#endif
	}
#ifdef DBG
	cerr << '\n';
#endif
    return ret;
}
// 1. flip horizontally
// 2. inverse i and j indices
void rotate(vector<vector<int>>& board)
{
    vector<vector<int>> inv(board[0].size());    // j i
    flip_hori(board);
    for (int j = 0; j < board[0].size(); j++)
        for (int i = 0; i < board.size(); i++)
            inv[j].push_back(board[i][j]);
    board = inv;
}
void flip_hori(vector<vector<int>>& board)
{
    int size = board.size();
    for (int i = 0; i+i < size; i++)
        swap(board[i], board[size-1 - i]);
}
void input(istream& is, vector<vector<int>>& board)
{
    int n, m;
    is >> n >> m;
    board = vector<vector<int>>(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            is >> board[i][j];
}
ostream& operator<<(ostream& os, const vector<vector<int>>& board)
{
    for (auto i : board){
        for (auto j : i)
            os << j << ' ';
        os << '\n';
    }

    return os;
}
