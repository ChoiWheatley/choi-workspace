/*
	<APSS> Chapter6 ID: BOARDCOVER
	<AUTHOR>: ChoiWheatley
	<HISTORY>:
	21. 02. 06 
		-- start and do it myself
---

H*W 크기의 게임판이 있습니다. 게임판은 검은 칸과 흰 칸으로 구성된 격자 모양을 하고 있는데 이 중 모든 흰 칸을 3칸짜리 L자 모양의 블록으로 덮고 싶습니다. 이 때 블록들은 자유롭게 회전해서 놓을 수 있지만, 서로 겹치거나, 검은 칸을 덮거나, 게임판 밖으로 나가서는 안 됩니다. 위 그림은 한 게임판과 이를 덮는 방법을 보여줍니다.

게임판이 주어질 때 이를 덮는 방법의 수를 계산하는 프로그램을 작성하세요.

입력

력의 첫 줄에는 테스트 케이스의 수 C (C <= 30) 가 주어집니다. 각 테스트 케이스의 첫 줄에는 2개의 정수 H, W (1 <= H,W <= 20) 가 주어집니다. 다음 H 줄에 각 W 글자로 게임판의 모양이 주어집니다. # 은 검은 칸, . 는 흰 칸을 나타냅니다. 입력에 주어지는 게임판에 있는 흰 칸의 수는 50 을 넘지 않습니다.

출력

한 줄에 하나씩 흰 칸을 모두 덮는 방법의 수를 출력합니다.

예제 입력

3
3 7
#.....#
#.....#
##...##
3 7
#.....#
#.....#
##..###
8 10
##########
#........#
#........#
#........#
#........#
#........#
#........#
##########
예제 출력

0
2
1514

	
*/
#include <iostream>
#include <fstream>		// for test cases with ease USING ifstream class
#include <vector>
#include <string>
#include <cstring>		// for use memcpy
#include <stdexcept>	// for use std::runtime_error class
#include <cstdlib>
#include <unistd.h>		// for use sleep()
using namespace std;

// global variables below
#define BLACK '#'
#define WHITE '.'
typedef unsigned char uchar;
constexpr int MAX_W = 20;
const uchar L_block[4][2][2] = {
	{
		{'#','#'},
		{'#','.'}
	},{
		{'#','#'},
		{'.','#'}
	},{
		{'.','#'},
		{'#','#'}
	},{
		{'#','.'},
		{'#','#'}
	}
};


/* function declarations below */
void input(istream& is, uchar (*board)[MAX_W], int h, int w);
int f(uchar board[MAX_W][MAX_W], const int& h, const int& w);
bool is_fit(const uchar (*board)[MAX_W], int i, int j, int& block_form);
uchar ** fill_block(const uchar (*board)[MAX_W], int i, int j, int block_form);
/* helper functions below */
template<typename T> void clear_matrix(T (*board)[MAX_W], T t);
ostream& operator<<(ostream& os, const uchar (*board)[MAX_W]);
void istream_recover(istream& is);
int count_white(const uchar (*board)[MAX_W]);
void delete_board(uchar *** board);
bool block_or(uchar, uchar);


///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
int main(void)
{
	int c, h, w;
	uchar (*board)[MAX_W] = new uchar [MAX_W][MAX_W];
	ifstream ifs{"sample.txt"};
	if (!ifs) std::runtime_error("wrong input file");
cerr << "제출하기 전에는 ifs->cin 으로 변경할 것!\n";
	ifs >> c;
	for (; c > 0; c--){
		ifs >> h >> w;
		input(ifs, board, h, w);
//debug
cout << board;
//enddebug
		// if every color in the board is already BLACK, print 0
		if (count_white(board) == 0) {
			cout << "0\n";
			continue;
		}
		cout << f(board, h, w) << '\n';
	}
	

	return 0;
}
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
void input(istream& is, uchar (*board)[MAX_W], int h, int w)
{
	clear_matrix(board, static_cast<uchar>(0));
	for (int i = 0; i < h; i++){
		is >> board[i];
		if (!is) istream_recover(is);
	}
}
int f(uchar board[MAX_W][MAX_W], const int& h, const int& w)
{
//BASE_CONDITION: if every color in the board is BLACK, return 1
	if (count_white(board) == 0) return 1;
	
	int ret = 0;
	int block_form = -1;
	for (int i = 0; i < h-1; i++){
		for (int j = 0; j < w-1; j++){
			if (is_fit(board, i, j, block_form)){
				uchar **new_block = fill_block(board, i, j, block_form);
				ret += f((uchar (*)[MAX_W])new_block, h, w);
//debug
//cerr << "(i,j) = ("<<i<<","<<j<<"), new_block = \n" << (uchar (*)[MAX_W])new_block;
//sleep(1);
//enddebug
			}
		}
	}
	return ret;
}
bool is_fit(const uchar (*board)[MAX_W], int i, int j, int& block_form)
{
	for (block_form = 0; block_form < 4; block_form++){
		uchar piece[2][2] = {
			{L_block[block_form][0][0], L_block[block_form][0][1]},
			{L_block[block_form][1][0], L_block[block_form][1][1]}
		};
		if (!(piece[0][0] == BLACK && board[i][j] 		== BLACK) &&
			!(piece[0][1] == BLACK && board[i][j+1] 	== BLACK) &&
			!(piece[1][0] == BLACK && board[i+1][j] 	== BLACK) &&
			!(piece[1][1] == BLACK && board[i+1][j+1] 	== BLACK)) return true; 
	}
	return false;
}
uchar ** fill_block(const uchar (*board)[MAX_W], int i, int j, int block_form)
{
	if (block_form == -1) cerr << "block_form not initialized!\n";
	uchar (*ret)[MAX_W] = new uchar[MAX_W][MAX_W];
	memcpy(ret, board, sizeof(uchar)*MAX_W*MAX_W);
//debug
//cerr << "ret = \n" << (uchar (*)[MAX_W])(*board);
//sleep(1);
//enddebug
	for (int y = 0; y <= 1; y++){
		for (int x = 0; x <= 1; x++){
			if (L_block[block_form][y][x] == WHITE) continue;
			ret[i+y][j+x] = L_block[block_form][y][x];
		}
	}
	return (uchar **)ret;
}
template<typename T> void clear_matrix(T (*board)[MAX_W], T t)
{
	for (int i = 0; i < MAX_W; i++){
		for (int j = 0; j < MAX_W; j++){
			board[i][j] = t;
	}	}
}
ostream& operator<<(ostream& os, const uchar (*board)[MAX_W])
{
	for (int i = 0; i < MAX_W; i++){
		if (board[i][0] == static_cast<uchar>(0)) break;
		os << board[i] << '\n';
	}
	return os;
}
void istream_recover(istream& is)
{
	if (is.good()) return;
	if (is.eof()){
		;
	} else if (is.fail()){
		is.clear(ios_base::goodbit);
	} else if (is.bad()){
		std::runtime_error("ios badbit occured");
	}
}
int count_white(const uchar (*board)[MAX_W])
{
	int ret = 0;
	for (int i = 0; i < MAX_W; i++){
		for (int j = 0; j < MAX_W; j++){
			if (board[i][j] == WHITE) ret++;
		}
	}
	return ret;
}
void delete_board(uchar *** board)
{
	for (int i = 0; i < MAX_W; i++)
		delete[] *board[i];
	delete[] *board;
}
bool block_or(uchar a, uchar b)
{
	if (a == BLACK && b == BLACK) return false;
	return true;
}
