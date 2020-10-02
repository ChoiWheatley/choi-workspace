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

/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 */
int main(void)
{
    int n = 0, k = 0;
    cout << "Please input 'n' and 'k' which infers 'choose k elements from the sequence 0 to n'\n$ ";
    cin >> n >> k;
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
 * base case : k == 0인 경우에 picked를 출력한다.
 * 각 함수는 원소를 하나씩만 picked에 넣고 나머지 k-1개의 조합은 재귀함수로 찾는다.
 */ 
{
    if ( k == 0 ) print_combi(picked);
    for (int i = 0; i < n; i++)
    {
        if (!is_dupl(i, picked))
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