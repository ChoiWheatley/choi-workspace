/*
    src: https://algospot.com/judge/problem/read/WILDCARD
*/
#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<string>
#include<sstream>
using namespace std;

vector<string> solve(const string& src, const vector<string>& pat);
bool isPatMatch(const string& src, const string& pat, 
                size_t src_pos, size_t pat_pos);

int main(int argc, char ** argv)
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
        if (isPatMatch(src, i, 0, 0))
            ret.push_back(i);
    }
    return ret;
}
bool isPatMatch(const string& src, const string& pat, 
                size_t src_pos, size_t pat_pos)
{
#ifdef DBG
    cerr<<"\t{ "<<src[src_pos] <<", " <<pat[pat_pos] << " }\n";
#endif//dbg

    while( (src_pos<src.size() && pat_pos<pat.size()) &&
           (src[src_pos]=='?' || pat[pat_pos]==src[src_pos]) )
    {
        ++src_pos;
        ++pat_pos;
    }

    //1. src_pos가 '*'을 만난 경우
    if (src[src_pos] == '*')
    {
<<<<<<< HEAD
        // * 안에 몇 개의 글자가 들어갈 지 모르기 때문에 
        // 0개부터 시작하여 하나씩 추가해 가며 재귀를 돈다.
        for (size_t skip=pat_pos; skip<=pat.size(); ++skip)
=======
        // src 마지막 문자가 *인 경우
        if (src_pos+1 == src.size())
            return true;
        // * 안에 몇 개의 글자가 들어갈 지 모르기 때문에 
        // 0개부터 시작하여 하나씩 추가해 가며 재귀를 돈다.
        for (size_t skip=pat_pos; skip<pat.size(); ++skip)
>>>>>>> 25ecbc4915fb7d3905ae45f2e97da27ad81e4873
        {
            if ( isPatMatch( src, pat, src_pos+1, skip ) )
                return true;
        }
    }

    //2. src_pos 가 끝에 도달한 경우
    if ( src_pos>=src.size()  &&  pat_pos>=pat.size() )
        return true;

    //3. 패턴매칭에 실패한 경우
    return false;
}
