/*
    src: https://algospot.com/judge/problem/read/TRIANGLEPATH
*/

#include<iostream>
#include<vector>
#include<cstdlib>
#include<cstdlib>
#include<climits>
#include<cstring>
#include<cmath>
using namespace std;

#define MAX 100
#define ERROR LONG_MAX
#define UNDEFINED 0
size_t cache[MAX][MAX]={0};     // 0 means undefined

void init_triangle(vector< vector<size_t> >& src, int size);
void input_triangle(vector< vector<size_t> >& src, istream& ist);
ostream& operator<<(ostream& os, const vector< vector<size_t> >& src);
size_t brute_force(const vector< vector<size_t> >& src, int y, int x);


int main(void)
{
    int c;
    cin>>c;
    vector< vector<size_t> > triangle;
    while(c-->0)
    {
        int n;
        cin>>n;
        memset(cache, 0, MAX*MAX*8);
        init_triangle(triangle, n);
        input_triangle(triangle, std::cin);
        #ifdef DBG
            cout << triangle << '\n';
        #endif
        cout << brute_force(triangle, 0, 0)<< "\n";
    }
    return 0;
}

// f(y,x) =  max(
//               f(y+1,x) + src[y][x],
//               f(y+1,x+1) + src[y+1][x]
//               )
size_t brute_force(const vector< vector<size_t> >& src, int y, int x)
{
    if (y < x)
        return ERROR;

    if ((size_t)y >= src.size())
        return 0;

    if (cache[y][x]!=UNDEFINED)
        return cache[y][x];

#ifdef DBG
    fprintf(stderr, "\tsrc[%d][%d]=%ld\n",y,x,src[y][x]);
#endif//DBG
    return ( cache[y][x]=
            max(
                brute_force(src, y+1, x) + src[y][x],
                brute_force(src, y+1, x+1) + src[y][x]
               )    
           );
}

void init_triangle(vector< vector<size_t> >& src, int size)
{
    src = vector< vector<size_t> >(size);
    for (int i = 0; i < size; i++)
        src[i] = vector<size_t>(i+1);
}

void input_triangle(vector< vector<size_t> >& src, istream& ist)
{
    for(size_t i=0; i < src.size(); i++)
    {
        for (size_t j=0; j < src[i].size(); j++)
        {
            ist >> src[i][j];
        }
    }
}

ostream& operator<<(ostream& os, const vector< vector<size_t> >& src)
{
    for (size_t i=0; i < src.size(); i++)
    {
        for (size_t j=0; j < src[i].size(); j++)
        {
            os << src[i][j] << ' ';
        }
        os << '\n';
    }
    os << '\n';
    return os;
}

