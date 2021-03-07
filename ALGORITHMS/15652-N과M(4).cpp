/*
문제
자연수 N과 M이 주어졌을 때, 아래 조건을 만족하는 길이가 M인 수열을 모두 구하는 프로그램을 작성하시오.

1부터 N까지 자연수 중에서 M개를 고른 수열
같은 수를 여러 번 골라도 된다.
고른 수열은 비내림차순이어야 한다.
길이가 K인 수열 A가 A1 ≤ A2 ≤ ... ≤ AK-1 ≤ AK를 만족하면, 비내림차순이라고 한다.
입력
첫째 줄에 자연수 N과 M이 주어진다. (1 ≤ M ≤ N ≤ 8)

출력
한 줄에 하나씩 문제의 조건을 만족하는 수열을 출력한다. 중복되는 수열을 여러 번 출력하면 안되며, 각 수열은 공백으로 구분해서 출력해야 한다.

수열은 사전 순으로 증가하는 순서로 출력해야 한다.

예제 입력 1  복사
3 1
예제 출력 1  복사
1
2
3
예제 입력 2  복사
4 2
예제 출력 2  복사
1 1
1 2
1 3
1 4
2 2
2 3
2 4
3 3
3 4
4 4
예제 입력 3  복사
3 3
예제 출력 3  복사
1 1 1
1 1 2
1 1 3
1 2 2
1 2 3
1 3 3
2 2 2
2 2 3
2 3 3
3 3 3
*/
#include<iostream>
#include<vector>
using namespace std;

void combi(vector<int> selected, const int& n, const int& m);
ostream& operator<<(ostream& os, const vector<int>& selected);

int main(void)
{
    int n, m;
    cin >> n >> m;
    combi(vector<int>{}, n, m);
    return 0;
}   
void combi(vector<int> selected, const int& n, const int& m)
{
    // BASE CONDITION
    if (selected.size() == m) {
        cout << selected << '\n';
        return;
    }

    int last = 1;
    if (selected.size() > 0) last = selected.back();
    for (int i = last; i <= n; i++){
        selected.push_back(i);
        combi(selected, n, m);
        selected.pop_back();
    }
}
ostream& operator<<(ostream& os, const vector<int>& selected)
{
    for (auto i : selected)
        os << i << ' ';
    return os;
}
