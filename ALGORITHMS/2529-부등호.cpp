/*
문제
두 종류의 부등호 기호 ‘<’와 ‘>’가 k개 나열된 순서열  A가 있다. 우리는 이 부등호 기호 앞뒤에 서로 다른 한 자릿수 숫자를 넣어서 모든 부등호 관계를 만족시키려고 한다. 예를 들어, 제시된 부등호 순서열 A가 다음과 같다고 하자.

A =>  < < < > < < > < >

부등호 기호 앞뒤에 넣을 수 있는 숫자는 0부터 9까지의 정수이며 선택된 숫자는 모두 달라야 한다. 아래는 부등호 순서열 A를 만족시키는 한 예이다.

3 < 4 < 5 < 6 > 1 < 2 < 8 > 7 < 9 > 0

이 상황에서 부등호 기호를 제거한 뒤, 숫자를 모두 붙이면 하나의 수를 만들 수 있는데 이 수를 주어진 부등호 관계를 만족시키는 정수라고 한다. 그런데 주어진 부등호 관계를 만족하는 정수는 하나 이상 존재한다. 예를 들어 3456128790 뿐만 아니라 5689023174도 아래와 같이 부등호 관계 A를 만족시킨다.

5 < 6 < 8 < 9 > 0 < 2 < 3 > 1 < 7 > 4

여러분은 제시된 k개의 부등호 순서를 만족하는 (k+1)자리의 정수 중에서 최댓값과 최솟값을 찾아야 한다. 앞서 설명한 대로 각 부등호의 앞뒤에 들어가는 숫자는 { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }중에서 선택해야 하며 선택된 숫자는 모두 달라야 한다.

입력
첫 줄에 부등호 문자의 개수를 나타내는 정수 k가 주어진다. 그 다음 줄에는 k개의 부등호 기호가 하나의 공백을 두고 한 줄에 모두 제시된다. k의 범위는 2 ≤ k ≤ 9 이다.

출력
여러분은 제시된 부등호 관계를 만족하는 k+1 자리의 최대, 최소 정수를 첫째 줄과 둘째 줄에 각각 출력해야 한다. 단 아래 예(1)과 같이 첫 자리가 0인 경우도 정수에 포함되어야 한다. 모든 입력에 답은 항상 존재하며 출력 정수는 하나의 문자열이 되도록 해야 한다.

예제 입력 1  복사
2
< >
예제 출력 1  복사
897
021
*/
#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<string>
#include<climits>
#include<stdexcept>
using namespace std;

int K = 0;
string minimum = "";
string maximum = "";

void input(istream& is, vector<char>& angles);
void digit(const vector<char>& angles, bool used[10], int angle_idx=0, string num="");
bool is_possible(const vector<char>& angle, const bool used[10], const string& num);
string strmin(string a, string b);
string strmax(string a, string b){ if(strmin(a,b) == a) return b; else return a; }
char itoc(int i);

int main(void)
{
	vector<char> angles;
#if DBG > 0
	fstream ifs{"sample.txt"};
	if (!ifs) { cerr<<"file opening error\n"; return 1; }
	while(true){
		input(ifs, angles);
		if (!ifs) break;
		//TODO
		bool used[10] = {false};
		digit(angles, used);
		cout << "maximum = " << maximum << '\n' << "minimum = " << minimum << '\n';
	}
#else
	input(cin, angles);
	bool used[10] = {false};
	digit(angles, used);
	cout << maximum << '\n' << minimum << '\n';
#endif
	return 0;
}
void input(istream& is, vector<char>& angles)
{
	is >> K;
	angles = vector<char>(K);
	for (int i = 0; i < K; i++){
		is >> angles[i];
		if (angles[i] != '<' && angles[i] != '>') throw runtime_error("angle error!");
	}
}
void digit(const vector<char>& angles, bool used[10], int angle_idx, string num)
{
	// init minimum and maximum
	if (angle_idx == 0) { 
#if DBG > 1
cerr << "num = " << num << '\n';
#endif
		maximum = string(K,'9');
		minimum = string(K,'0');
	}
	// BASE CONDITION - success
	if (angle_idx == angles.size()) {
		minimum = strmin(minimum, num);
		maximum = strmax(maximum, num);
		return;
	}
	// BASE CONDITION - failure
	if (!is_possible(angles, used, num)) return;

	// 몰라 일단 넣고보자
	for (int i = 0; i < 10; i++){
		if (used[i]) continue;
		used[i] = true;
		num.push_back(itoc(i));
		digit(angles, used, angle_idx+1, num);

		used[i] = false;
		num.pop_back();
	}
}
string strmin(string a, string b)
{
	for (int i = 0; i < K; i++){
		if (a[i] > b[i]) return a;
		if (a[i] < b[i]) return b;
	}
	// identical case can happen
	return a;
}
// check the whole angle-digit conditions
bool is_possible(const vector<char>& angle, const bool used[10], const string& num)
{
	if (num.size() == 0) return true;
	for (int i = 0; i < num.size()-1; i++){
		if (angle[i] == '<' && !(num[i] < num[i+1])) return false;
		if (angle[i] == '>' && !(num[i] > num[i+1])) return false;
	}
	return true;
}
char itoc(int i)
{
	if ( 0 <= i && i <= 9 ) return (i + '0');
	return 0;
}
