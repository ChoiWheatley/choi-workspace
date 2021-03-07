/*
지금까지 배운 것을 종합해서, 한국으로 돌아오는 비행기에서 규현이는 종이에 수를 N개 썼다. (규현이가 아는 가장 큰 수는 10이기 때문에, 수를 10개까지만 쓸 수 있다.)  그 다음에, 가능한 모든 N*(N+1)/2개의 구간의 합을 구했다. 이 것을 해인이는 행렬로 표현했다.

규현이가 쓴 수를 A라고 하면, A[i]는 규현이가 i번째 쓴 수이다. 그리고, S[i][j]는 A[i]부터 A[j]까지 합이 0보다 크면 +, 0이면 0, 0보다 작으면 -이다. 여기서 i는 항상 j보다 작거나 같다. 이렇게 배열을 채우면 배열에는 총 N*(N+1)/2개의 문자가 있다. (+, -, 0 중 하나) 이 S 배열이 주어졌을 때, 규현이가 쓴 N개의 수 A를 구해서 출력하면 된다. 규현이는 -10부터 10까지의 정수밖에 모르기 때문에, A도 -10부터 10까지의 정수로만 이루어져 있어야 한다.

입력
첫째 줄에 수열의 크기 N이 주어진다. N은 10보다 작거나 같은 자연수이다. 둘째 줄에는 N(N+1)/2 길이의 문자열이 주어진다. 처음 N개의 문자는 부호 배열의 첫 번째 줄에 해당하고, 다음 N-1개의 문자는 두 번째 줄에 해당한다. 마찬가지로 마지막 문자는 N번째 줄에 해당하는 문자다.

출력
첫째 줄에 수열의 원소 N개를 빈 칸을 사이에 두고 출력한다. 답이 여러 가지 일 경우에는 아무거나 출력하면 된다.

예제 입력 1  복사
4
-+0++++--+
예제 출력 1  복사
-2 5 -3 1
*/
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<stdexcept>
using namespace std;

int N = 0;

bool iterate(const string& s, vector<int>& assume, int idx = 0);
bool is_valid(const string& s, const vector<int>& assume, int idx);
/*helperfunction*/
inline void input(istream& is, string& s) { is >> N; is >> s; }
inline char mapping(const string& s, int i, int j) { return s[i*(2*N-i-1)/2 + j]; }

int main(void)
{
#if DBG > 0
	ifstream ifs{"sample.txt"};
	if (!ifs) return 2;
	for(;true;){
		string s;
		input(ifs, s);
		vector<int> assume(N);
		cout << "s = " << s << "  mapped version =  ";
		for (int i = 0; i < N; i++){
			for (int j = i; j < N; j++){
				cout << mapping(s, i, j);
			}
		}
		cout << '\n';
		
		if (!iterate(s, assume)) cout << "no results\n";
		for (auto i : assume) cout << i << ' ';
		cout << '\n';
		if (!ifs) break;
	}
#else
	string s;
	input(cin, s);
	vector<int> assume(N);
	iterate(s, assume);
	for (auto i : assume) cout << i << ' ';
	cout << '\n';
#endif
	return 0;
}
bool iterate(const string& s, vector<int>& assume, int idx)
{
	// BASE_CONDITION-failure
	if (idx > 0 && !is_valid(s, assume, idx-1)) return false;
	// BASE_CONDITION-success
	if (idx == N) {
		return true;
	} 

	if (mapping(s, idx, idx) == '0') {
		assume[idx] = 0;	// 말할것도 없지
		if (iterate(s, assume, idx+1)) return true;
	} else if (mapping(s, idx, idx) == '-') {
		for (int i = -10; i < 0; i++){
			assume[idx] = i;
			if (iterate(s, assume, idx+1)) return true;
		}
	} else if (mapping(s, idx, idx) == '+') {
		for (int i = 1; i <= 10; i++){
			assume[idx] = i;
			if (iterate(s, assume, idx+1)) return true;
		}
	}
	return false;
}
bool is_valid(const string& s, const vector<int>& assume, int idx)
{
	int sum = 0;
	for(int i = idx; i >= 0; --i){
#if DBG > 1
cout << "assume["<<i<<"]="<< assume[i] <<'\n';
#endif
		sum += assume[i];
		switch(mapping(s, i, idx)){
		case '-':
			if (!(sum < 0)) return false;
			break;
		case '0':
			if (!(sum == 0)) return false;
			break;
		case '+':
			if (!(sum > 0)) return false;
			break;
		}
	}
	return true;
}