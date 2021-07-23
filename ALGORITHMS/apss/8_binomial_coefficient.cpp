#include<iostream>
#include<string>
#include<vector>
#include<unistd.h>
#include<climits>
using namespace std;

#define MAX 1000
unsigned long long cnt_stupid=0, cnt_memo=0;
vector< vector<int> > memo(MAX, vector<int>(MAX, -1));

int bino_stupid(int n, int r);
int bino_memoization(int n, int r);

int main(int argc, char ** argv)
{
    int n=25, r=12;
    if (argc == 3)
    {
        n = stoi(argv[1]);
        r = stoi(argv[2]);
    }
    // bino :: stupid version
    cout << "(" << n << ", " << r << ") =\n";
    cout << bino_stupid(n, r) << ", count=" << cnt_stupid << '\n';

    // bino :: memoization version
    cout << bino_memoization(n, r) << ", count=" << cnt_memo << '\n';
    
    return 0;
}
int bino_stupid(int n, int r)
{
    if (n <= r || r == 0)   
        return 1;
    cnt_stupid++;
    return bino_stupid(n-1, r-1) + bino_stupid(n-1, r);
}
int bino_memoization(int n, int r)
{
    if (n <= r || r == 0)
        return 1;
    cnt_memo++;
    int& ref_memo = memo[n][r];
    if (ref_memo != -1)
        return ref_memo;

    return (ref_memo = bino_memoization(n-1, r) + bino_memoization(n-1, r-1));
}
