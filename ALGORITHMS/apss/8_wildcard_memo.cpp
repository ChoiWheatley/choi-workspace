#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
enum DP{
    UNDEFINED=-1, FAILURE=0, SUCCESS=1
};

#define MAXN 100
#define MAXC (MAXN+1)
static int cache[MAXC][MAXC]={-1};

vector<string> solve(const string& src, const vector<string>& pat);
bool isPatMatch(const string& src, const string& pat, 
                size_t s, size_t p);

int main(int argc, char **argv)
{
    int c;
    cin >> c;
    while(c-->0)
    {
        int n;
        string src;
        vector<string> pat;
        
        cin >> src;
        cin >> n;
        while(n-->0)
        {
            string tmp;
            cin >> tmp;
            pat.push_back(tmp);
        }

#ifdef DBG
        cout << "\n\tsrc: " << src << '\n';
        cout << "\tpat: \n\t[ ";
        for (auto i : pat)
            cout << i << ", ";
        cout << "\b\b ]\n";
#endif// DBG

        // TODO: solve problem
        vector<string> answer = solve(src, pat);
        for (auto i : answer)
            cout << i << "\n";
    }
    return 0;
}

vector<string> solve(const string& src, const vector<string>& pat)
{
    vector<string> ret;
    for (const string& i : pat)
    {
        memset( cache, -1, MAXC*MAXC );
        if ( isPatMatch(src, i, 0, 0)==SUCCESS )
            ret.push_back(i);
    }
    sort(ret.begin(), ret.end());
    return ret;
}

bool isPatMatch(const string& src, const string& pat, 
                size_t s, size_t p)
{
#ifdef DBG
    fprintf( stderr,"\t\t[ %s, %s ]  \tcache[%lu,%lu]=%d\n", 
        &src[s], &pat[p], s,p, cache[s][p] );
#endif 

    int& ret = cache[s][p];
    if (ret != UNDEFINED)
        return ret;

    if( (s<src.size() && p<pat.size()) &&
            (src[s]=='?' || pat[p]==src[s]) )
        return ( ret = isPatMatch(src,pat,s+1,p+1) );

    // s,p가 동시에 마지막을 가리키고 있는 경우
    if ( s==src.size() && p==pat.size() )
        return (ret = SUCCESS);

    // '*'을 만난 경우
    if ( src[s]=='*' )
    {
        if ( isPatMatch(src,pat,s+1,p)==SUCCESS ||      // 0개 
                (p<pat.size() && isPatMatch(src,pat,s,p+1)==SUCCESS) )//1개 이상
            return (ret = SUCCESS);
    }

    // 패턴매칭 실패
    return (ret = FAILURE);
}
