/*
    src: https://algospot.com/judge/problem/read/LIS
*/
#include<iostream>
#include<string>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
using namespace std;

#define MAXCACHE 500
#define UNDEFINED -1
static int cache[MAXCACHE] = {UNDEFINED};

int bruteforce(const vector<int>& sequence, vector<int>::iterator it, int max_val=0);
int using_dp(const vector<int>& sequence, vector<int>::iterator it, int max_val=0);

int main(void)
{
    int c;
    cin >> c;
    while(c-->0)
    {
        int n;
        cin >> n;
        vector<int> sequence(n);
        memset(cache, UNDEFINED, MAXCACHE * sizeof(*cache)); 
        for (int i = 0; i < n; i++)
        {
            cin >> sequence[i];
        }
        cout << using_dp(sequence, sequence.begin())<<'\n';
        #ifdef DBG
            cout << "\nbruteforce::" << bruteforce(sequence, sequence.begin()) << "\n";
        #endif
    }
    return 0;
}

int bruteforce(const vector<int>& sequence, vector<int>::iterator it, int max_val)
{
    if (it == sequence.end())
        return 0;

    int ret = 0;
#ifdef DBG
    fprintf(stderr, "[%lu]=%d\t", it-sequence.begin(), *it);
#endif

    // 부분수열에 넣는다.
    if (max_val < *it)
        ret = max( ret, 1 + bruteforce(sequence, it+1, *it) );

    // 지나친다.
    ret = max( ret, bruteforce(sequence, it+1, max_val) );

    return ret;
}

int using_dp(const vector<int>& sequence, vector<int>::iterator it, int max_val)
{
    if (it == sequence.end())
        return 0;
    int ret = 0;
    size_t index = it - sequence.begin();

    if (cache[index] != UNDEFINED)
    {
        return cache[index];
    }
#ifdef DBG
    fprintf(stderr, "[%lu]=%d\t", index, *it);
#endif

    // 부분수열에 넣는다.
    if (max_val < *it)
        ret = max( ret, 1 + bruteforce(sequence, it+1, *it) );

    // 지나친다.
    else
        ret = max( ret, bruteforce(sequence, it+1, max_val) );

    return (cache[index] = ret);
}
