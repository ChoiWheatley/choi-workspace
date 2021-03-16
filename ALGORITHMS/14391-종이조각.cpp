/*
문제
영선이는 숫자가 쓰여 있는 직사각형 종이를 가지고 있다. 종이는 1×1 크기의 정사각형 칸으로 나누어져 있고, 숫자는 각 칸에 하나씩 쓰여 있다. 행은 위에서부터 아래까지 번호가 매겨져 있고, 열은 왼쪽부터 오른쪽까지 번호가 매겨져 있다.

영선이는 직사각형을 겹치지 않는 조각으로 자르려고 한다. 각 조각은 크기가 세로나 가로 크기가 1인 직사각형 모양이다. 길이가 N인 조각은 N자리 수로 나타낼 수 있다. 가로 조각은 왼쪽부터 오른쪽까지 수를 이어 붙인 것이고, 세로 조각은 위에서부터 아래까지 수를 이어붙인 것이다.

아래 그림은 4×4 크기의 종이를 자른 한 가지 방법이다.



각 조각의 합은 493 + 7160 + 23 + 58 + 9 + 45 + 91 = 7879 이다.

종이를 적절히 잘라서 조각의 합을 최대로 하는 프로그램을 작성하시오.

입력
첫째 줄에 종이 조각의 세로 크기 N과 가로 크기 M이 주어진다. (1 ≤ N, M ≤ 4)

둘째 줄부터 종이 조각이 주어진다. 각 칸에 쓰여 있는 숫자는 0부터 9까지 중 하나이다.

출력
영선이가 얻을 수 있는 점수의 최댓값을 출력한다.

예제 입력 1  복사
2 3
123
312
예제 출력 1  복사
435
예제 입력 2  복사
2 2
99
11
예제 출력 2  복사
182
예제 입력 3  복사
4 3
001
010
111
100
예제 출력 3  복사
1131
예제 입력 4  복사
1 1
8
예제 출력 4  복사
8
*/
#include<iostream>
#include<cmath>
#include<algorithm>
#include<string>
#define IST std::cin
using namespace std;

#if DBG > 0
#include<fstream>
#include<stdexcept>
#include<iomanip>
#undef IST
#define IST ifs
ifstream IST{"sample.txt"};
#endif


/* GLOBAL VARIABLES */
#define MAXN 4
#define HORI 0
#define VERT 1

/* FUNCTION DECLATATIONS */
void input(istream& is, int board[MAXN][MAXN], int& n, int& m);
int calc(const int board[MAXN][MAXN], int n, int m);
int shad(const int board[MAXN][MAXN], const unsigned int bitwise, const int n, const int m, unsigned int& bit_selected, int i, int j, unsigned int delta);
int bit_map(unsigned int bitwise, int m, int i, int j);
void print_bit(unsigned int bitwise, int n, int m);


int main(void)
{
    for (;;)
    {
        int board[MAXN][MAXN] = {-1};
        int n = 0, m = 0;
        input(IST, board, n, m);
#if DBG > 1
for (int i = 0; i < n; i++){
	for (int j = 0; j < m; j++)
		std::cerr << board[i][j] << ' ';
	std::cerr << '\n';
}
#endif
        if (!IST) break;

        cout << calc(board, n, m) << '\n';
    }
    return 0;
}
void input(istream& is, int board[MAXN][MAXN], int& n, int& m)
{
    for (int i = 0; i < MAXN * MAXN; i++) *(*board+i) = -1;
    is >> n >> m;
    
    for (int i = 0; i < n; i++){
		is.ignore(10, '\n');
        for (int j = 0; j < m; j++){
			char tmp = 0;
			is.get(tmp);
			if (!isdigit(tmp)) is.clear(ios_base::failbit);
			board[i][j] = tmp - '0';
       }
	}
}
int calc(const int board[MAXN][MAXN], int n, int m)
{
    int ret = -1;
	unsigned int bitwise = 0;	// bitwise size is maximum MAXN * MAXN, which can be 16
    for (bitwise = 0; bitwise < (unsigned int)(1<<(n*m)); bitwise++){
#if DBG > 1
std::cerr << "\nbitwise:";
print_bit(bitwise, n, m);
#endif
		int sum = 0;
		unsigned int bit_selected = 0;
		for (int i = 0; i < n; i++){
			for (int j = 0; j < m; j++){
				sum += shad(board, bitwise, n, m, bit_selected, i, j, bit_map(bitwise, m, i, j));
			}
		}
		ret = max(ret, sum);
	}

    return ret;
}
// bitwise 값을 토대로 board의 값을 더해서 출력한다.
int shad(const int board[MAXN][MAXN], const unsigned int bitwise, const int n, const int m, unsigned int& bit_selected, int i, int j, unsigned int delta)
{
	// BASE CONDITION
	if ( i >= n || j >= m ) return 0;
	if ( (unsigned int)bit_map(bitwise, m, i, j) != delta ) return 0;
	if ( bit_map(bit_selected, m, i, j) == 1) return 0;		// is [i][j] already visited

	int ret = board[i][j], shad_ = 0, digit = 0;
	// TODO TODO TODO TODO TODO TODO
	switch( delta ){
	case HORI:
		bit_selected |= (1<<(i*m+j));
		shad_ = shad(
			board, bitwise, n, m,
			bit_selected,
			i, j+1,
			bit_map(bitwise, m, i, j)
		);
		digit = to_string(shad_).size();
		ret = ret*pow(10,digit) + shad_;
		break;
	case VERT:
		bit_selected |= (1<<(i*m+j));
		shad_ = shad(
			board, bitwise, n, m,
			bit_selected,
			i+1, j,
			bit_map(bitwise, m, i, j)
		);
		digit = to_string(shad_).size();
		ret = ret*pow(10,digit) + shad_;
		break;
	}
	

#if DBG > 1
std::cerr << ret << '\t';
#endif

	return ret;
}
int bit_map(unsigned int bitwise, int m, int i, int j)
{
	return ( (bitwise>>(i*m+j)) & 1 );
}
void print_bit(unsigned int bitwise, int n, int m)
{
	for (int i = 0; i < n; i++){
		std::cerr << '\n';
		for (int j = 0; j < m; j++){
			std::cerr << bit_map(bitwise, m, i, j);
		}
	}
	std::cerr << '\n';
}
