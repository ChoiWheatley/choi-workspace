/*
문제
수빈이는 TV를 보고 있다. 수빈이는 채널을 돌리려고 했지만, 버튼을 너무 세게 누르는 바람에, 일부 숫자 버튼이 고장났다.

리모컨에는 버튼이 0부터 9까지 숫자, +와 -가 있다. +를 누르면 현재 보고있는 채널에서 +1된 채널로 이동하고, -를 누르면 -1된 채널로 이동한다. 채널 0에서 -를 누른 경우에는 채널이 변하지 않고, 채널은 무한대 만큼 있다.

수빈이가 지금 이동하려고 하는 채널은 N이다. 어떤 버튼이 고장났는지 주어졌을 때, 채널 N으로 이동하기 위해서 버튼을 최소 몇 번 눌러야하는지 구하는 프로그램을 작성하시오. 

수빈이가 지금 보고 있는 채널은 100번이다.

입력
첫째 줄에 수빈이가 이동하려고 하는 채널 N (0 ≤ N ≤ 500,000)이 주어진다.  둘째 줄에는 고장난 버튼의 개수 M (0 ≤ M ≤ 10)이 주어진다. 고장난 버튼이 있는 경우에는 셋째 줄에는 고장난 숫자 버튼이 주어지며, 같은 버튼이 여러 번 주어지는 경우는 없다.

출력
첫째 줄에 채널 N으로 이동하기 위해 버튼을 최소 몇 번 눌러야 하는지를 출력한다.

예제 입력 1  복사
5457
3
6 7 8
예제 출력 1  복사
6
예제 입력 2  복사
100
5
0 1 2 3 4
예제 출력 2  복사
0
예제 입력 3  복사
500000
8
0 2 3 4 6 7 8 9
예제 출력 3  복사
11117
힌트
5455++ 또는 5459--
*/
#include<iostream>
#include<vector>
#include<fstream>
#include<cmath>
#include<string>
#include<algorithm>
using namespace std;

#define DBG

constexpr int current = 100;
void input (istream& is, vector<int>& intact_btn, int& target);
int closest(const int& target, const vector<int>& intact_btn);
vector<int> next_selection(vector<int> intact_btn, int digit);
int combi_as_int(vector<int> combi);

int main(void)
{
    vector<int> intact_btn{0,1,2,3,4,5,6,7,8,9};
    int target = 0;
    int a = 0, b = 0;
#ifdef DBG
    ifstream ifs{"sample.txt"};
    if (!ifs) return 1;
    input(ifs, intact_btn, target);
    for (auto i : intact_btn)
        cerr << i << ", ";
    cerr << "\b\b\n";
#else
    input(cin, intact_btn, target);
#endif

    a = closest(target, intact_btn);
    b = abs(target - current);
    cout << min(a, b) << '\n';

    return 0;
}

void input (istream& is, vector<int>& intact_btn, int& target)
{
    int m, brkn;
    vector<int>::iterator brkn_it;
    is >> target;
    is >> m;
    for (; m>0; --m){
        is >> brkn;
        brkn_it = find(intact_btn.begin(), intact_btn.end(), brkn);
        intact_btn.erase(brkn_it, brkn_it+1);
    }
}
int closest(const int& target, const vector<int>& intact_btn)
{
    int digit = to_string(target).size();
    // you don't need to push '0' at first time
}
// duplication-ok selection: case = pow(intact_btn.size(), digit)
vector<int> next_selection(vector<int> intact_btn, int digit)
// BASE_CONDITION : digit < 1이면 return last btn number
{
    int n = intact_btn.size();
    
}
int combi_as_int(vector<int> combi)
{
    int ret = 0;
    for (auto i : combi)
        ret = (ret * 10) + i;
    return ret;
}
