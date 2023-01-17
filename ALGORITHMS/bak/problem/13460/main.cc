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
#include<cstdlib>
#include<string>
#include<sstream>
#include<unistd.h>
#include<climits>
using namespace std;

typedef struct
{
    int red[2];
    int blue[2];
    int hole[2];
} State;

#define MAX_B 10
int n, m;
unsigned char board[MAX_B+1][MAX_B+1];
enum dir { up=0, right, down, left };
const int delta_x[] = {-1, 0, 1, 0};
const int delta_y[] = {0, 1, 0, -1};
vector< vector<int> > fail_red;
vector< vector<int> > fail_blue;


void myinput();
int tilt(enum dir dir, int count);
// helper function
void init_board(unsigned char board[][MAX_B+1]);
string print_board(unsigned char board[MAX_B+1][MAX_B+1], int n, int m);
inline int min(int a, int b);
inline bool is_same_coord(const int a[2], const int b[2]);
void move_marble(unsigned char board[][MAX_B+1], const int from[2], const int to[2]); 
State get_board_state(const unsigned char board[][MAX_B+1]);
void set_board_state(unsigned char board[][MAX_B+1], const State s);
void copy_state(State& dest, State& src);
bool operator==(const State& a, const State& b);
bool operator!=(const State& a, const State& b){ return !(a==b); }

int main(void)
{
    int count = 10;
    init_board(board);
    myinput();
    cout << print_board(board, n, m);
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
        return INT_MAX;

    // direction 방향대로 구슬을 움직인다.
    State before = get_board_state(board);
    State after;
    do
    {
        after.red[0] = before.red[0] + delta_x[d];
        after.red[1] = before.red[1] + delta_x[d];
        after.blue[0] = before.blue[0] + delta_y[d];
        after.blue[1] = before.blue[1] + delta_y[d];
        if (board[after.red[0]][after.red[1]] == '.')
        {
        }
    }while(before != after);
    // 기존 방향을 제외한 나머지 세 방향을 시도한다.

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
string print_board(unsigned char board[MAX_B+1][MAX_B+1], int n, int m)
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
inline bool is_same_coord(const int a[2], const int b[2])
{
    return (a[0] == b[0] && a[1] == b[1]);
}
void move_marble(unsigned char board[][MAX_B+1], const int from[2], const int to[2])
{
    char from_val = board[from[0]][from[1]];
    board[from[0]][from[1]] = '.';
    board[to[0]][to[1]] = from_val;

    cerr << print_board(board, n, m) << '\n';
}
State get_board_state(const unsigned char board[][MAX_B+1])
{
    State ret;
    for (int i = 0; i < MAX_B; i++)
    {
        for (int j = 0; j < MAX_B; j++)
        {
            switch(board[i][j])
            {
            case 'R':
                ret.red[0] = i;
                ret.red[1] = j;
                break;
            case 'B':
                ret.blue[0] = i;
                ret.blue[1] = j;
                break;
            case '0':
                ret.hole[0] = i;
                ret.hole[1] = j;
            }
        }
    }
    return ret;
}
void set_board_state(unsigned char board[][MAX_B+1], const State s)
{
    for (int i = 0; i < MAX_B; i++)
        for (int j = 0; j < MAX_B; j++)
            if (board[i][j] == 'R' || board[i][j] == 'B')
                board[i][j] = '.';
    board[s.red[0]][s.red[1]] = 'R';
    board[s.blue[0]][s.blue[1]] = 'B';
    board[s.hole[0]][s.hole[1]] = '0';
}
bool operator==(const State& a, const State& b)
{
    return (a.red[0] == b.red[0]
            && a.red[1] == b.red[1]
            && a.blue[0] == b.blue[0]
            && a.blue[1] == b.blue[1]
            && a.hole[0] == b.hole[0]
            && a.hole[1] == b.hole[1]
    );
}
void copy_state(State& dest, State& src)
{
    for (int i = 0; i < 2; i++)
    {
        dest.red[i] = src.red[i];
        dest.blue[i] = src.blue[i];
        dest.hole[i] = src.hole[i];
    }
}
