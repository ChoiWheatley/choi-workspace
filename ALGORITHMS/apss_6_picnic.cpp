/*
	<APSS> Chapter6 ID: PICNIC
	Author : ChoiWheatley
	History :
	{
	-- 2021. 02. 04.
		?????
	-- 2021. 02. 03.
		start
	}
	TIPS:
	{
		https://stackoverflow.com/questions/11543625/passing-an-array-as-a-const-argument-of-a-method-in-c
			which describes about passing a "const reference" of array
	}
안드로메다 유치원 익스프레스반에서는 다음 주에 율동공원으로 소풍을 갑니다. 원석 선생님은 소풍 때 학생들을 두 명씩 짝을 지어 행동하게 하려고 합니다. 그런데 서로 친구가 아닌 학생들끼리 짝을 지어 주면 서로 싸우거나 같이 돌아다니지 않기 때문에, 항상 서로 친구인 학생들끼리만 짝을 지어 줘야 합니다.

각 학생들의 쌍에 대해 이들이 서로 친구인지 여부가 주어질 때, 학생들을 짝지어줄 수 있는 방법의 수를 계산하는 프로그램을 작성하세요. 짝이 되는 학생들이 일부만 다르더라도 다른 방법이라고 봅니다. 예를 들어 다음 두 가지 방법은 서로 다른 방법입니다.

(태연,제시카) (써니,티파니) (효연,유리)
(태연,제시카) (써니,유리) (효연,티파니)

입력

입력의 첫 줄에는 테스트 케이스의 수 C (C <= 50) 가 주어집니다. 각 테스트 케이스의 첫 줄에는 학생의 수 n (2 <= n <= 10) 과 친구 쌍의 수 m (0 <= m <= n*(n-1)/2) 이 주어집니다. 그 다음 줄에 m 개의 정수 쌍으로 서로 친구인 두 학생의 번호가 주어집니다. 번호는 모두 0 부터 n-1 사이의 정수이고, 같은 쌍은 입력에 두 번 주어지지 않습니다. 학생들의 수는 짝수입니다.

출력

각 테스트 케이스마다 한 줄에 모든 학생을 친구끼리만 짝지어줄 수 있는 방법의 수를 출력합니다.

예제 입력

3
2 1
0 1
4 6
0 1 1 2 2 3 3 0 0 2 1 3
6 10
0 1 0 2 1 2 1 3 1 4 2 3 2 4 3 4 3 5 4 5

예제 출력

1
3
4
*/

#include <iostream>
#include <cstdio>
#include <fstream>
#include <iomanip>	// to use std::setw() function
#include <string>
#include <vector>
#include <algorithm>
#include <utility>	// to use swap() function
#define MAX_N 10
using namespace std;
typedef unsigned char uchar;
//
//
//
void input(istream& is, uchar unpaired[MAX_N], uchar friends[MAX_N][MAX_N], int& n);
int count_pair(uchar unpaired[MAX_N], const uchar (&friends)[MAX_N][MAX_N] , const int& n);
//for debugging, print vector
ostream& operator<<(ostream& os, const uchar * list);
ostream& operator<<(ostream& os, const uchar matrix[MAX_N][MAX_N]);
ostream& print_matrix(ostream& os, uchar** matrix);
uchar ** matrix_init();
void clear_list(uchar ls[MAX_N]);
void clear_matrix(uchar matrix[MAX_N][MAX_N]);
void delete_matrix(uchar ** matrix);
void rotate_matrix(uchar ** matrix);
bool base_condition(uchar unpaired[MAX_N]);
int find_idx(uchar ls[MAX_N], uchar f);
//
//
//
int main(void)
{
	ifstream fs{"sample.txt"};
	if (!fs) throw std::runtime_error("error opening an file");
	uchar unpaired[MAX_N];
	uchar friends[MAX_N][MAX_N];
	clear_list(unpaired);
	clear_matrix(friends);
	int c, n;
	fs >> c;
	for (; c > 0; c--){
		input(fs, unpaired, friends, n);
//debug
//cout << "DEBUG: unpaired: \n" << unpaired << "\nfriends:" << friends << '\n';
//end debug
		cout << count_pair(unpaired, friends, n) << '\n';
	}
	return 0;
}
//
//
//


void input(istream& is, uchar unpaired[MAX_N], uchar friends[MAX_N][MAX_N], int& n)
{
	// initialize unpaired and friends into 0
	clear_list(unpaired);
	clear_matrix(friends);

	int m;			// m : number of pairs	  (0<=m<=(n(n-1)/2))
	is >> n >> m;
	for (int i = 0; i < n; i++){
		unpaired[i] = 1;
	}
	for (int i = 0; i < m; i++){
		int tmp1, tmp2;
		is >> tmp1 >> tmp2;
		if (tmp1 > tmp2) swap(tmp1, tmp2);		// I'll only use one side of friends matrix
		friends[tmp1][tmp2] = 1;
	}
} // void input()
int count_pair(uchar unpaired[MAX_N], const uchar (&friends)[MAX_N][MAX_N] , const int& n)
{
/// Base_Condition: Every student is paired (= no unpaired one)
	if (base_condition(unpaired)) return 1;
///
//find very first unpaired one
	int very_first = find_idx(unpaired, 1);
	int ret = 0;
	for (int i = very_first+1; i < n; i++){
		//GOTCHA: unpaired ones and both are friends
		if (unpaired[i] && friends[very_first][i]){
			unpaired[i] = unpaired[very_first] = 0;
			ret += count_pair(unpaired, friends, n);
			unpaired[i] = unpaired[very_first] = 1;
	}	}	
	return ret;
}
ostream& operator<<(ostream& os, const uchar * ls)
{
	os << "[";
	if (ls == nullptr) { os << "no elements]\n"; return os;}
	for (int i = 0; i < MAX_N; i++){
		os << (int)ls[i] << ", ";
	}
	os << "\b\b]\n";
	return os;
}
ostream& operator<<(ostream& os, const uchar matrix[MAX_N][MAX_N])
{
	os << '\n';
	for (int i = 0 ; i < MAX_N; i++){
		os << matrix[i];
	}
	return os;
}
ostream& print_matrix(ostream& os, uchar** matrix)
{
	if (matrix == nullptr) {os << "[no elements]\n"; return os;}
	for (int i = 0; i < MAX_N; i++){
		os << matrix[i];
	}
	os << "\n";
	return os;
}
uchar ** matrix_init()
{
	uchar ** ret = new uchar*[MAX_N];
	for (int i = 0; i < MAX_N; i++){
		ret[i] = new uchar[MAX_N]{0};
	}
	return ret;
}
void clear_list(uchar ls[MAX_N])
{
	for (int i = 0; i < MAX_N; i++)
		ls[i] = 0;
}
void clear_matrix(uchar matrix[MAX_N][MAX_N])
{
	for (int i = 0; i < MAX_N; i++)
		for (int j = 0; j < MAX_N; j++)
			matrix[i][j] = 0;
}
void rotate_matrix(uchar ** matrix)
{
//debug
//cerr << "original matrix : \n" << matrix << "\n";
//enddebug
//1. i,j converse
//2. j inverse
	for (int i = 0; i < MAX_N; i++){
		for (int j = i; j < MAX_N; j++){
			swap(matrix[i][j], matrix[j][i]);
		}
	}
	for (int j = 0; j < MAX_N/2; j++){
		swap(matrix[j], matrix[MAX_N-j-1]);
	}
//debug
//cerr << "rotated matrix : \n" << matrix << "\n";
//enddebug
}
void delete_matrix(uchar ** matrix)
{
	for (int i = 0; i < MAX_N; i++)
		delete [] matrix[i];
	delete [] matrix;
}
bool base_condition(uchar unpaired[MAX_N])
{
	bool flag = true;
	for (int i = 0; i < MAX_N; i++)
		if (unpaired[i] == 1) flag = false;
	return flag;
}
int find_idx(uchar ls[MAX_N], uchar f)
{
	for (int i = 0; i < MAX_N; i++)
		if (ls[i] == f) return i;
	return -1;
}
