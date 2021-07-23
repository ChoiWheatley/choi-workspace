/*
    https://algospot.com/judge/problem/read/JUMPGAME
*/
#include<iostream>
#include<cstring>

#define MAXN 100

int memo[MAXN][MAXN] = {-1};
int board[MAXN][MAXN] = {0};

void input(int board[MAXN][MAXN], int& n);
int jumpgame(const int y, const int x, const int n);

int main(int argc, char ** argv)
{
    int c, n;
    std::cin >> c;
    while(c-->0)
    {
        input(board, n);
        
        std::cout << (jumpgame(0, 0, n) ? "YES" : "NO") << '\n';
    }
    return 0;
}
void input(int& n)
{
    memset(board, 0, MAXN*MAXN);
    memset(memo, -1, MAXN*MAXN);
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cin >> board[i][j];
        }
    }
}
int jumpgame(const int y, const int x, const int n)
{
    if (y==n-1 && x==n-1) 
        return 1;
    if (y>=n || x>=n)
        return 0;

    int& ref = memo[y][x];
    if ( ref!=-1 )
        return ref;
    int jump=board[y][x];
    return (
        ref = jumpgame(y+jump, x, n) ||
        jumpgame(y, x+jump, n)
    );
}
