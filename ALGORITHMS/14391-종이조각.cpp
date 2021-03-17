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
int all_segments(const int board[MAXN][MAXN], const unsigned int bitwise, int n, int m, int delta);
int bit_map(unsigned int bitwise, int m, int i, int j);
void print_bit(unsigned int bitwise, int n, int m);


int main(void)
{

#if DBG > 0
    for (;;)
    {
#endif
		int board[MAXN][MAXN] = {-1};
		int n = 0, m = 0;
		input(IST, board, n, m);
		
		// TODO
		int sum = 0;
		for (int bitwise = 0; bitwise < (1 << (n*m)); bitwise++){
			sum = max(sum, all_segments(board, bitwise, n, m, HORI));
			sum = max(sum, all_segments(board, bitwise, n, m, VERT));
		}
		std::cout << sum << '\n';
#if DBG > 0
	}
#endif

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
int all_segments(const int board[MAXN][MAXN], const unsigned int bitwise, int n, int m, int delta)
{
	int sum = 0;



	if (delta == HORI){
		for (int i = 0; i < n; i++){
			for (int j = 0; j < m; j++){
				if ( bit_map( bitwise, m, i, j ) == delta ){
					int seg = 0;

					// 다른 게 나오거나 끝 까지 갈 때 까지 숫자를 반복하여 더해준다.
					for (;    j < m && bit_map( bitwise, m, i, j ) == delta    ; j++)
						seg = seg*10 + board[i][j];

					sum += seg;
				}
			}
		}
	}
	else if (delta == VERT){	
		for (int j = 0; j < m; j++){
			for (int i = 0; i < n; i++){
				if ( bit_map( bitwise, m, i, j ) == delta ){
					int seg = 0;
					
					for (;    i < n && bit_map( bitwise, m, i, j ) == delta    ; i++)
						seg = seg*10 + board[i][j];

					sum += seg;
				}
			}
		}
	}

	return sum;
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
