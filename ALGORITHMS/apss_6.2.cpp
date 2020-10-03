/*
 * < 중첩 반복문 대체하기 >
 * recursive function으로 n 개의 원소 
 * 중 m개를 고르는 모든 조합 (combination)을 출력하시오.
 */ 

#include <iostream>
#include <vector>

using namespace std;

void combination(int n, int k, vector<int> & picked);
void print_combi(const vector<int> & combi);
bool is_dupl(int i, const vector<int> & combi);
inline bool is_bigger(int i, const vector<int> & combi);

/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 */
int main(void)
{
    int n = 0, k = 0;
    cout << "Please input 'n' and 'k' which infers 'n Combination of k'\n>>> ";
    cin >> k >> n;
    combination(n, k, *(new vector<int>));
    
    return 0;
}
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 */

void combination(int n, int k, vector<int> & picked)
/*
 * pre-condition : n < 4인 경우, 오류를 내고 프로그램을 종료한다.
 * base case : k == 0인 경우에 picked를 출력한다.
 * base case : picked.empty()인 경우에 0을 집어넣는다.
 * 각 함수는 원소를 하나씩만 picked에 넣고 나머지 k-1개의 조합은 재귀함수로 찾는다.
 */ 
{
    static int count = 0;
    if ( n < k ) throw runtime_error("'n' should be bigger than k");
    if ( k == 0 ) 
    {
        print_combi(picked);
        count++;
        return;
    }
    for (int i = 0; i < n; i++)
    {
        /* permutation 을 구하는 코드였다.
        if (!is_dupl(i, picked))
        {
            picked.push_back(i);
            combination(n, k-1, picked);
            picked.pop_back();
        }
        */
        // combination
        if (is_bigger(i, picked))
        {
            picked.push_back(i);
            combination(n, k-1, picked);
            picked.pop_back();
        }
    }
}
void print_combi(const vector<int> & combi)
{
    static int count = 0;

    cout << "(";
    for (auto i : combi)
        cout << i << " ";
    cout << "\b)";

    if (!(++count % 10))
        cout << endl;
}
bool is_dupl(int i, const vector<int> & combi)
{
    for (auto j : combi)
    {
        if (i == j) return true;
    }
    return false;
}

inline bool is_bigger(int i, const vector<int> & combi)
{
    if (combi.empty())
        return true;
    if (i > combi.back())
        return true;
    else 
        return false;
}