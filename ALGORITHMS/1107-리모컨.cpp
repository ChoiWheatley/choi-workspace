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
#include<algorithm>
#include<string>
#include<cmath>
using namespace std;

//#define DBG

#define N 500000
#define C 2*N
#define NOW 100

bool possible(int c, const vector<bool>& broken);

int main(void)
{
    int target, m, tmp;
    vector<bool> broken(10, false);
// Input
    cin >> target;
    for (cin >> m; m>0; --m){
        cin >> tmp;
		broken[tmp] = true;
    }

// chanel search
    int ans = abs(target - NOW);
    for (int c = 0; c <= C; c++){
        if (possible(c, broken)){
#ifdef DBG
			cerr << "c = " << c << '\n';
#endif
            int tmp_ans = abs(target - c);      //+,- push out of distance
            tmp_ans += to_string(c).size();     //times of numpad push
            if (tmp_ans < ans) ans = tmp_ans;
        }
    }
    cout << ans << '\n';

    return 0;
}
// is c pushable??
bool possible(int c, const vector<bool>& broken)
{
	if (c == 0) return broken[0] ? false : true;
    for (; c > 0; c /= 10){                 // c/=10 means go next to digit
		if (broken[c%10]) return false;    // c%10 means the first digit
    }
    return true;
}
