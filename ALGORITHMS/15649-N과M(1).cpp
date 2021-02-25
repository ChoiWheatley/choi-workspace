/*
문제
자연수 N과 M이 주어졌을 때, 아래 조건을 만족하는 길이가 M인 수열을 모두 구하는 프로그램을 작성하시오.

1부터 N까지 자연수 중에서 중복 없이 M개를 고른 수열
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
1 2
1 3
1 4
2 1
2 3
2 4
3 1
3 2
3 4
4 1
4 2
4 3
예제 입력 3  복사
4 4
예제 출력 3  복사
1 2 3 4
1 2 4 3
1 3 2 4
1 3 4 2
1 4 2 3
1 4 3 2
2 1 3 4
2 1 4 3
2 3 1 4
2 3 4 1
2 4 1 3
2 4 3 1
3 1 2 4
3 1 4 2
3 2 1 4
3 2 4 1
3 4 1 2
3 4 2 1
4 1 2 3
4 1 3 2
4 2 1 3
4 2 3 1
4 3 1 2
4 3 2 1
*/
#include<iostream>
#include<vector>
using namespace std;
void permu(vector<int> selected, const int& n, const int& m);
std::ostream& operator<<(std::ostream& os, const vector<int>& selected);
int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    permu(vector<int>{}, n, m);

    return 0;
}
void permu(vector<int> selected, const int& n, const int& m)
{
    // BASE_CONDITION
    if (selected.size() == m) { std::cout << selected << '\n'; return; }

    for (int i = 1; i <= n; i++){
        bool continue_flag = false;
        for (auto j : selected) 
            if (i == j) continue_flag = true;
        if (continue_flag) continue;
        selected.push_back(i);
        permu(selected, n, m);
        selected.pop_back();
    }
}
std::ostream& operator<<(std::ostream& os, const vector<int>& selected)
{
    for (auto i : selected)
        os << i << ' ';
    return os;
}
