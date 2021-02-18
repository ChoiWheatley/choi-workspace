/*
문제
양수 A가 N의 진짜 약수가 되려면, N이 A의 배수이고, A가 1과 N이 아니어야 한다. 어떤 수 N의 진짜 약수가 모두 주어질 때, N을 구하는 프로그램을 작성하시오.

입력
첫째 줄에 N의 진짜 약수의 개수가 주어진다. 이 개수는 50보다 작거나 같은 자연수이다. 둘째 줄에는 N의 진짜 약수가 주어진다. 1,000,000보다 작거나 같고, 2보다 크거나 같은 자연수이고, 중복되지 않는다.

출력
첫째 줄에 N을 출력한다. N은 항상 32비트 부호있는 정수로 표현할 수 있다.

예제 입력 1  
2
4 2
예제 출력 1 
8
*/
#include<iostream>
#include<string>
#include<vector>
#include<stdexcept>
#include<cmath>
using namespace std;
//#define DBG

int find_N(const vector<int>& real_aliquot);
vector<int> gen_real_aliquot(int n);

int main()
{
// ORIGINAL ANSWER
/* 
	int n = 0;
	int *min = nullptr;
	int *max = nullptr;
	int tmp = 0;
	cin >> n;
	for (; n>0; n--){
		cin >> tmp;
		if (min == nullptr && max == nullptr) { min = new int(tmp); max = new int(tmp); }
		if (tmp < *min) *min = tmp;
		else if (*max < tmp) *max = tmp;
	}
	cout << (*min)*(*max) << '\n';
*/
// DEBUGGING
	for (int i = 4; ;i++){
		vector<int> real_aliquots = gen_real_aliquot(i);
#ifdef DBG
cerr << i << "= [ ";
for (int i : real_aliquots)
	cerr << i << " ";
cerr << "]\n";
#endif
		if (real_aliquots.size() > 50) break;
		if (real_aliquots.size() == 0 || find_N(real_aliquots) == 0) continue;
		if (i != find_N(real_aliquots)) std::runtime_error("i != find_N()");
		cout << "i = " << i << ", find_N() = " << find_N(real_aliquots) << '\n';
	}
	
	return 0;
}


int find_N(const vector<int>& real_aliquot)
{
	
	int *min = nullptr;
	int *max = nullptr;
	for (int i : real_aliquot){
		if (min == nullptr && max == nullptr) { min = new int(i); max = new int(i); }
		if (i < *min) *min = i;
		else if (*max < i) *max = i;
	}
	return (*min) * (*max);
}
// no prime number ('cause size of real aliquot is zero)
// maximum n = gen_real_aliquot(n).size() == 50
vector<int> gen_real_aliquot(int n)
{
	int maxI = sqrt(n);
	vector<int> ret;
	for (int i = 2; i <= maxI; i++){
		if (n%i == 0) { 
			if (i*i == n) ret.push_back(i);
			else { ret.push_back(i); ret.push_back(n/i); }
		}
	}
	return ret;
}
