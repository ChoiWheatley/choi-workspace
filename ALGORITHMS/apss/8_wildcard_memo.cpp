#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
enum DP{
    UNDEFINED=-1, FAILURE=0, SUCCESS=1
};

#define MAXN 101
static char cache[MAXN][MAXN]={-1};

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
        cout << "\tsrc: " << src << '\n';
        cout << "\tpat: \n\t[ ";
        for (auto i : pat)
            cout << i << ", ";
        cout << "\b\b ]\nanswer:\n";
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
        memset( cache, -1, MAXN*MAXN );
        if ( isPatMatch(src, i, 0, 0) )
            ret.push_back(i);
    }
    return ret;
}

bool isPatMatch(const string& src, const string& pat, 
                size_t s, size_t p)
{
    auto& ret = cache[s][p];
#ifdef DBG
    cerr<<"\t[ "<< src << ", " << pat
        <<" ]:\t[ "<< src[s] << "," << pat[p]
        << "("<<(int)ret<<")" <<" ]\n";
#endif
    if (ret != UNDEFINED)
        return ret;
    while ( (s<src.size() && p<pat.size()) &&
            (src[s]=='?' || src[s]==pat[p]) )
    {
        s++; 
        p++;
    }

    // 1. * 을 만난 경우, (s+1, p) 를 서로 비교한다.
    if ( src[s]=='*' )
    {
        for (size_t skip=p; skip<=pat.size(); ++skip)
        {
            if (isPatMatch(src,pat, s+1, skip))
                goto success;
        }
    }

    // 2. src, pat 모두 end를 바라보고 있다
    if ( s>=src.size() && p>=pat.size() )
        goto success;

    // 3. 나머지는 전부 패턴매칭 실패
    goto failure;

success:
    return (ret = SUCCESS);
failure:
    return (ret = FAILURE);
}
