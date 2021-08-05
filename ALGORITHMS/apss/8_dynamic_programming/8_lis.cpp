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
#include<algorithm>
using namespace std;

#define MAXCACHE 500
#define UNDEFINED -1
static int cache[MAXCACHE] = {UNDEFINED};

int bruteforce(const vector<int>& sequence, vector<int>::iterator it, int max_val=0);
int using_dp(vector<int>& sequence);
int using_dp_iter(const vector<int>& sequence, vector<int>::iterator it, int maxval=UNDEFINED);
int efficient_lis(const vector<int>& seq);
vector<int> efficient_list(const vector<int>& seq);
vector<int> efficient_list_re(const vector<int>& seq);

int main(void)
{
    int c;
    cin >> c;
    while(c-->0)
    {
        int n, ret;
        cin >> n;
        vector<int> sequence(n);
        for (int i = 0; i < n; i++)
        {
            cin >> sequence[i];
        }

        #if DBG==1
        for (auto i : sequence)
            cout<< i << ' ';
        cout <<'\n';
        #endif


        vector<int> lis = efficient_list_re(sequence);

        #if DBG==1
        for (auto i : lis)
            cout<<i<< ' ';
        cout<<"\n=";
        #endif

        cout<<lis.size()<<'\n';


        #ifdef DBG
        cout << "efficient_list::";
        lis = efficient_list(sequence);
        for (auto i : lis)
            cout << i << ' ';
        cout << " size = " << lis.size() << '\n';
        cout << "bruteforce::" << bruteforce(sequence, sequence.begin()) << '\n';
        cout << "dp::" << using_dp(sequence) << '\n';
        cout << "efficient_lis::" << efficient_lis(sequence) << "\n----------\n";
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
//    fprintf(stderr, "[%lu]=%d\t", it-sequence.begin(), *it);
#endif

    // 부분수열에 넣는다.
    if (max_val < *it)
        ret = max( ret, 1 + bruteforce(sequence, it+1, *it) );

    // 지나친다.
    ret = max( ret, bruteforce(sequence, it+1, max_val) );

    return ret;
}

// it으로 시작하는 LIS의 길이
int using_dp(vector<int>& sequence)
{
    int ret = 0;
    for (vector<int>::iterator i = sequence.begin(); i != sequence.end(); i++)
    {
        memset(cache, UNDEFINED, sizeof(cache));
        ret = max( ret, using_dp_iter(sequence, i) );
    }
    return ret;
}

int using_dp_iter(const vector<int>& sequence, vector<int>::iterator it, int max_val)
{
    if (it == sequence.end())
        return 0;
    if (max_val == UNDEFINED)
    {
        max_val = *it;
    }
    size_t index = it - sequence.begin();
    int& ret = cache[index];

    if (ret != UNDEFINED)
    {
        return ret;
    }
#if 0
    fprintf(stderr, "[%lu]=%d\t", index, *it);
#endif
    
    // 항상 1+a개를 구하기 때문에 1부터 시작.
    ret=1;
    // max_val 보다 뒤에 있고 큰 수들 중 하나를 결정한 뒤
    // 여기서 시작하는 부분증가수열의 최대치를 구해 비교한다.
    while(++it != sequence.end())
    {
        // 부분수열에 넣는다.
        if (max_val < *it)
            ret = max( ret, 1 + using_dp_iter(sequence, it, *it) );
    }

    return ret;
}
int efficient_lis(const vector<int>& seq)
{
    int L = 0, newL;
    memset(cache, 0, sizeof(cache));

    // cache[0]은 사용하지 않는다는 것을 염두하세요.
    for(size_t i = 0; i < seq.size(); i++)
    {
        // seq[i] > seq[m[j]]를 만족하는 가장 큰 j를 찾는다.
        int lo=1, hi=L;
        while (lo<=hi)
        {
            int mid = (lo+hi) / 2;
            if (seq[i] > seq[cache[mid]])
                lo = mid+1;
            else
                hi = mid-1;
        }
        newL = lo;
        cache[newL] = i;
        if (newL > L)
            L = newL;
    }

    return L;
}
vector<int> efficient_list(const vector<int>& seq)
{
    int P[MAXCACHE];
    int M[MAXCACHE+1];
    int L = 0, newL;
    memset(P, 0, sizeof(P));
    memset(M, 0, sizeof(M));

    for (size_t i = 0; i < seq.size(); i++)
    {
        // binary search for finding the largest 'j'
        // which satisfies X[M[j]] < X[i]
        int lo,hi;
        for (lo=1, hi=L; lo<=hi; )
        {
            int j = (lo+hi) / 2;
            if (seq[M[j]] < seq[i])
                lo = j+1;
            else
                hi = j-1;
        }
        // after this, lo is 1 greater than j
        // which will be substituted
        newL = lo;

        // P stores predecessor of X[k] where
        // k stands for the last index of ending
        // with X[k]
        P[i] = M[newL - 1];

        // M stores or replace the largest 'j'
        // which can be LIS
        M[newL] = i;

        #ifdef DBG
        fprintf(stderr, "i=%lu, X[M]=[", i);
        for (size_t j = 1; j < i; j++)
        {
            fprintf(stderr, "%d,", seq[M[j]]);
        }
        fprintf(stderr, "\b ]\tp[%lu]=%d\n", i, P[i]);
        #endif

        if (newL > L)
            L = newL;
    }

    // reconstruct LIS with backtracing
    // X[k]로 끝나는 LIS의 predecessor index를 따라
    // 내려가다보면 길이 L짜리인 LIS의 리스트를
    // 얻어낼 수 있다.
    vector<int> ret(L);
    int k = M[L];
    for (int i = L-1; i >= 0; --i)
    {
        ret[i] = k;
        k = P[k];
    }

    return  ret;
}

// X[i] : 입력으로 주어진 수열
// M[k] : 수열 X의 길이 k인 부분수열 중에서 마지막 인덱스의
// 값이 가장 작은 값을 저장.
// P[i] : X[i]가 바라보고 있는 M 배열의 인덱스
vector<int> efficient_list_re(const vector<int>& X)
{
    int M[MAXCACHE+1], P[MAXCACHE];
    int L = 0, newL;

    memset(M, 0, sizeof(M));
    memset(P, 0, sizeof(P));
    for (size_t i = 0; i < X.size(); ++i)
    {
        int lo = 1, hi = L, mid;
        // find lower bound using binary search
        while( lo<=hi )
        {
            mid = (lo+hi) / 2;
            if (M[mid] < X[i])
                lo = mid+1;
            else
                hi = mid-1;
        }
        // after binary search, lo gets 1 greater
        // than L

        // M replace (or append) new value X[i]
        // and P keeps tracking on M's index
        newL = lo;
        M[newL] = X[i];
        P[i] = newL;

        #if DBG==1
        fprintf(stderr,"newL=%d, M = [", newL);
        for (int j = 0; j <= newL; j++)   
            fprintf(stderr, "%d ", M[j]);
        fprintf(stderr, "]\tP[%lu]=%d\n", i, P[i]);
        #endif
        // when append we have to set hi value
        if (newL > L)
            L = newL;
    }

    // backtracking to get LIS
    // we only care when M gets appended!
    vector<int> ret(L);
    int r = L-1;
    for (int i = (int)X.size()-1; i >= 0; --i)
    {
        if (L == P[i])
        {
            ret[r--] = X[i];
            fprintf(stderr, "X[%d]=%d\n", i, X[i]);
            L--;
        }
    }

    return ret;
}
