/*
문제
두 자연수 A와 B가 있을 때, A = BC를 만족하는 자연수 C를 A의 약수라고 한다. 예를 들어, 2의 약수는 1, 2가 있고, 24의 약수는 1, 2, 3, 4, 6, 8, 12, 24가 있다. 자연수 A의 약수의 합은 A의 모든 약수를 더한 값이고, f(A)로 표현한다. x보다 작거나 같은 모든 자연수 y의 f(y)값을 더한 값은 g(x)로 표현한다.

자연수 N이 주어졌을 때, g(N)을 구해보자.

입력
첫째 줄에 테스트 케이스의 개수 T(1 ≤ T ≤ 100,000)가 주어진다. 둘째 줄부터 테스트 케이스가 한 줄에 하나씩 주어지며 자연수 N(1 ≤ N ≤ 1,000,000)이 주어진다.

출력
각각의 테스트 케이스마다, 한 줄에 하나씩 g(N)를 출력한다.

예제 입력 1  복사
5
1
2
10
70
10000
예제 출력 1  복사
1
4
87
4065
82256014
*/

/*
<TIP>
- g_tbl[i] = g_tbl[i-1] + f(i) 는 O(N^2) 또는 O(N√N)의 시간복잡도를 가지기에 너무 느리다.
    when you use the multiplication method, g_tbl can be drawn in O(N) time-complexity
<TODO>
- precompiled table?
*/
#include<iostream>
#include<cmath>
//#define DBG
#define N_MAX 1000000  // 10^6
#define T_MAX 100000   // 10^5
using namespace std;

typedef unsigned long long int ull;

ull f_tbl[N_MAX+1];
ull g_tbl[N_MAX+1];
void init_f_tbl();
void init_g_tbl();

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    init_f_tbl();
    init_g_tbl();
#ifdef DBG
cerr << "initialization g_tbl done!" << '\n';
#endif
    int t = 0;
    int input = 0;
    cin >> t;
    for (; t > 0; --t){
        cin >> input;
        cout << g_tbl[input] << '\n';
    }
    return 0;
}
void init_f_tbl()
{
    fill_n(f_tbl, N_MAX+1, 1);
    for (int i = 2; i <= N_MAX; i++){
        for (int j = 1; i*j <= N_MAX; j++){
            f_tbl[i*j] += i;
    }   }
}
void init_g_tbl()
{
    g_tbl[1] = 1;
    for (int i = 2; i <= N_MAX; i++){
        g_tbl[i] = g_tbl[i-1] + f_tbl[i];
    }
}

/* TOO slow
ull f(int k)
{
    ull ret = 0;
    for (int i = 1; i <= k; i++){
       if (k%i == 0) ret += i; 
    }
    return ret;
}
*/
