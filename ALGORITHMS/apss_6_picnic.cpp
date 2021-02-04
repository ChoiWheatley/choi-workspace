/*
	<APSS> Chapter6 ID: PICNIC
	Author : ChoiWheatley
	History :
	{
	-- 2021. 02. 03.
		start
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
#include <fstream>
#include <iomanip>	// to use std::setw() function
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void input(istream& is, vector<int>& unpaired, vector<int>& friends);
// iteration halt when two of friends are left
void count_pair(const vector<int>& unpaired, const vector<int>& friends, int& cnt);
//for debugging, print vector
ostream& operator<<(ostream& os, const vector<int>& list);
template<typename T>
bool find(const vector<T>& ls, const T& n);
template<typename T>
bool find(const vector<T>& ls, const T& n, const T& n1);

//
//
//
int main(void)
{
	ifstream fs{"sample.txt"};
	if (!fs) throw std::runtime_error("error opening an file");
	vector<int> unpaired;
	vector<int> friends;
	int c;
	fs >> c;
	for (; c > 0; c--){
		input(fs, unpaired, friends);
		//debug
		cerr << unpaired << friends << '\n';
		//end debug
		int cnt = 0;
		count_pair(unpaired, friends, cnt);
		cout << cnt << '\n';
	}
	return 0;
}
//
//
//



// iteration halt when two of friends are left
void count_pair(const vector<int>& unpaired, const vector<int>& friends, int& cnt)
{
//HALT_CONDITION: friends.size() == 2
	if (friends.size() == 2){
		if (find(unpaired, friends[0], friends[1])) cnt++;
		return;
	}
	for (int i = 0; i < friends.size(); i += 2){
		if (find(unpaired, friends[i], friends[i+1])) {
//debug
//enddebug
			count_pair(unpaired_, friends_, cnt);
		}
	}
}
void input(istream& is, vector<int>& unpaired, vector<int>& friends) 
{
	unpaired = vector<int>();
	friends  = vector<int>();
	int n, m;		// n : number of students (2<=n<=100)
					// m : number of pairs	  (0<=m<=(n(n-1)/2))
	is >> n >> m;
	for (int i = 0; i < n; i++){
		unpaired.push_back(i);
	}
	for (int i = 0; i < m*2; i++){
		int tmp;
		is >> tmp;
		friends.push_back(tmp);
	}
}
//for debugging, print vector
ostream& operator<<(ostream& os, const vector<int>& list)
{
	os << "list.size() : " << list.size() << " [\n";
	int cnt = 1;
	for (auto i : list) {
		os << setw(3) << i;
		if (cnt++ % 10 == 0) os << "\n";
	}
	os << "\n]\n";
	return os;
}

template<typename T>
bool find(const vector<T>& ls, T& n)
{
	for (int i = 0 ; i < ls.size() ; i++){
		if (n == ls[i]) return true;
	}
	return false;
}
template<typename T>
bool find(const vector<T>& ls, const T& n, const T& n1)
{
	bool retn = false;
	bool retn1 = false;
	for (auto i : ls){
		if (n == i) retn = true;
		if (n1 == i) retn1 = true;
	}
	return (retn && retn1);
}
