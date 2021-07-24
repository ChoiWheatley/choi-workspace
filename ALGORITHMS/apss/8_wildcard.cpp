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

vector<string>& solve(const string& src, vector<string>& pat);
bool isPatMatch(const string& src, const string& pat);

int main(int argc, char ** argv)
{
    int c;
    cin >> c;
    while(c-->0)
    {
        int n;
        string src;
        vector<string> pat;
        
        cin>> src;
        cin >> n;
        while(n-->0)
        {
            string tmp;
            cin >> tmp;
            pat.push_back(tmp);
        }

#if DBG == 0
        cout << "\tsrc: " << src << '\n';
        cout << "\tpat: \n\t[ ";
        for (auto i : pat)
            cout << i << ", ";
        cout << "\b\b ]\nanswer:\n";
#endif// DBG

        // TODO: solve problem
        vector<string>& answer = solve(src, pat);
        for (auto i : answer)
            cout << i << "\n";
    }
    return 0;
}

vector<string>& solve(const string& src, vector<string>& pat)
{
    vector<string>::iterator pat_it=pat.begin();
    while(pat_it != pat.end())
    {
        if (!isPatMatch(src, (const string)*pat_it))
        {
            #if DBG == 0
                cerr << "\t'" << *pat_it << "' is deleted\n";
            #endif
            pat_it = pat.erase (pat_it);
        }
        else
            pat_it++;
    }
    
    sort(pat.begin(), pat.end());
    return pat;
}
bool isPatMatch(const string& src, const string& pat)
{
    string::const_iterator src_it, pat_it;
    src_it = src.begin();
    pat_it = pat.begin();
    while( src_it != src.end() ||
           pat_it != pat.end() )
    {
        #if DBG==0
            cerr << "[src,pat]=[" << *src_it<<","<<*pat_it << "] ";
        #endif
        switch(*src_it)
        {
        case '?':
            // do nothing, just bypassing assessment
            break;
        case '*':
            // do iteration
            break;
        default:
            if (*src_it != *pat_it)
                return false;
            break;
        }
        src_it++;
        pat_it++;
    }

    return true;
}
