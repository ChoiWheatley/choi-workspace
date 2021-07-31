#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <algorithm>
#include <iomanip>
using namespace std;

vector<int> fence;

int solve(int begin, int end);

int main()
{
    int c;
    cin >> c;
    while(c-->0)
    {
        int n;
        cin >> n;
        fence=vector<int>(n);
        for (int i=0; i<n; i++)
        {
            cin >> fence[i];
        }
        cout << solve(0, n) << '\n';
    }
    return 0;
}
int solve(int begin, int end)
{
    // base cond: only one element left
    if (begin+1 == end)
        return fence[begin];
    // case [I]: [begin, pivot) 구간의 판자들 중에서 가장 큰 너비
    // case [II]:[pivot, end) 구간의 판자들 중에서 가장 큰 너비
    int pivot = (int)((begin+end) / 2);
    int ret = max(  solve(begin, pivot),    solve(pivot, end)  );
    
    // case [III]: pivot 인덱스를 포함하는 최대너비의 직사각형을 구한다.
    ret = max(ret,
        [&]() -> int
        {
            int lo=pivot, hi=pivot;
            int height=fence[pivot];
            int ret=height;
            while( begin<lo || hi<end-1 )
            {
                if (lo==begin && hi<end-1)
                {
                    hi++;
                    height=min( height, fence[hi] );
                }
                else if (hi==end-1 && begin<lo)
                {
                    lo--;
                    height=min( height, fence[lo] );
                }
                else if (fence[lo-1] < fence[hi+1])
                {
                    hi++;
                    height=min( height, fence[hi] );
                }
                else
                {
                    lo--;
                    height=min( height, fence[lo] );
                }
                ret=max( ret, height*(hi-lo+1) );
                //cerr<<"\t"<<lo<<"~"<<hi<<"="<<height*(hi-lo+1)<<setw(5)<<"\t(pivot="<<pivot<<")\n";
            }
            return ret;
        }()
    );

    return ret;
}
