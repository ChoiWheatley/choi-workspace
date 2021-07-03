/*
입력
첫 번째 줄에는 보드의 세로, 가로 크기를 의미하는 두 정수 N, M (3 ≤ N, M ≤ 10)이 주어진다. 다음 N개의 줄에 보드의 모양을 나타내는 길이 M의 문자열이 주어진다. 이 문자열은 '.', '#', 'O', 'R', 'B' 로 이루어져 있다. '.'은 빈 칸을 의미하고, '#'은 공이 이동할 수 없는 장애물 또는 벽을 의미하며, 'O'는 구멍의 위치를 의미한다. 'R'은 빨간 구슬의 위치, 'B'는 파란 구슬의 위치이다.

입력되는 모든 보드의 가장자리에는 모두 '#'이 있다. 구멍의 개수는 한 개 이며, 빨간 구슬과 파란 구슬은 항상 1개가 주어진다.

출력
최소 몇 번 만에 빨간 구슬을 구멍을 통해 빼낼 수 있는지 출력한다. 만약, 10번 이하로 움직여서 빨간 구슬을 구멍을 통해 빼낼 수 없으면 -1을 출력한다.


    4^10 = 1048576 Brute Force gogo
    Figure out how marbles react after tilting
*/

#include<iostream>
#include<vector>
#include<tuple>
#include<cstdlib>
#include<string>
#include<sstream>
using namespace std;

#define MAX_B 10
int n, m;
unsigned char board[MAX_B+1][MAX_B+1];
enum dir { up=0, right, down, left };
const int delta_x[] = {[dir::up]=-1, [dir::right]=0, [dir::down]=1, [dir::left]=0};
const int delta_y[] = {[dir::up]=0, [dir::right]=1, [dir::down]=0, [dir::left]=-1};


void myinput();
int tilt(enum dir dir, int count);
// helper function
void init_board(unsigned char board[][MAX_B+1]);
string print_board(unsigned char board[MAX_B+1][MAX_B+1]);
inline int min(int a, int b);
void whereis_marble(int ret[2], const unsigned char board[][MAX_B+1], char marble_color);
inline bool is_same_coord(const int a[2], const int b[2]);
void move_marble(unsigned char board[][MAX_B+1], const int from[2], const int to[2]); 

int main(void)
{
    int count = 10;
    init_board(board);
    myinput();
    cout << print_board(board);
    for (int i = 0; i < 4; i++)
    {
        count = min(count, tilt((enum dir)i, 1));
        if (0 < count && count <= 10)
        {
            cout << count << '\n';
            return 0;
        }
    }
    cout << -1 << '\n';
    return 0;
}
void myinput()
{
    cin >> n >> m;
    
    for (int i = 0; i < n; i++)
    {
        cin >> board[i];
    }
}
int tilt(enum dir d, int count)
{
    if (count > 10)
        return -1;
    // move marbles
    int red[2], delta_red[2];
    int blue[2], delta_blue[2];

    whereis_marble(red, board, 'R');
    whereis_marble(blue, board, 'B');
    do
    {
        delta_red[0] = red[0] + delta_y[d];
        delta_red[1] = red[1] + delta_x[d];
        if (board[delta_red[0]][delta_red[1]] == '.')
        {
            move_marble(board, red, delta_red);
            red[0] = delta_red[0];
            red[1] = delta_red[1];
        }

        delta_blue[0] = blue[0] + delta_y[d];
        delta_blue[1] = blue[1] + delta_x[d];
        if (board[delta_blue[0]][delta_blue[1]] == '.')
        {
            move_marble(board, blue, delta_blue);
            blue[0] = delta_blue[0];
            blue[1] = delta_blue[1];
        }
    } while(!(is_same_coord(red, delta_red) && is_same_coord(blue, delta_blue)));
           

    // next tilt
    int next = 10;
    for (int i = 0; i < 4; i++)
    {
        next = min(next, tilt((enum dir)i, count+1));
        if (0 < next && next <= 10)
            return next;
    }
    return -1;
}
// helper function
void init_board(unsigned char board[][MAX_B+1])
{
    for (int i = 0; i < MAX_B; i++)
    {
        for (int j = 0; j < MAX_B-1; j++)
        {
            board[i][j] = '#';
        }
    }
}
string print_board(unsigned char board[MAX_B+1][MAX_B+1])
{
    stringstream ret;
    ret << "{\n";
    for (int i = 0; i < n; i++)
    {
        ret << "\t{ " << board[i] << " }\n";
    }
    ret << "}\n";
    return ret.str();
}
inline int min(int a, int b)
{
    return (a < b ? a : b);
}
void whereis_marble(int ret[2], const unsigned char board[][MAX_B+1], char marble_color)
{
    for (int i = 0; i < MAX_B; i++)
    {
        for (int j = 0; j < MAX_B; j++)
        {
            if (board[i][j] == marble_color)
            {
                ret[0] = i;
                ret[1] = j;
            }
        }
    }
}

inline bool is_same_coord(const int a[2], const int b[2])
{
    return (a[0] == b[0] && a[1] == b[1]);
}
void move_marble(unsigned char board[][MAX_B+1], const int from[2], const int to[2])
{
    char from_val = board[from[0]][from[1]];
    board[from[0]][from[1]] = '.';
    board[to[0]][to[1]] = from_val;

    cerr << print_board(board) << '\n';
}
