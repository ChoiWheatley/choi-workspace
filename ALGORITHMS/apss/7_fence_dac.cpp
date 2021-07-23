#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> fence;

int solve(int begin, int end);

int main(void)
{
    int c, n;
    cin >> c;
    while (c-->0)
    {
        cin >> n;
        fence = vector<int>(n);
        for (int i = 0; i < n; i++)
        {
            cin >> fence[i];
        }
        cout << solve(0, n) << '\n';
    }
    return 0;
}
int solve(int begin, int end)
{
    // base case: 원소가 하나밖에 남지 않은 경우
    if (begin+1 == end) 
        return fence[begin];
    
    int ret = 1, pivot = (begin+end)/2;
    // case [I] : [ begin, (begin+end)/2 ) 구간에서의 최고값
    // case [II] : [ (begin+end)/2, end ) 구간에서의 최고값
    ret = max(solve(begin, pivot), solve(pivot, end));

    // case [III] : (begin+end)/2 에서부터 양쪽으로 넓혀가며 구한 가장 큰
    //              너비, 이때 양쪽 중 더 길이가 긴 판자 쪽으로 넓혀나간다.
    ret = max(ret, [&]() -> int {
        int lo = pivot, hi = pivot;
        int ret = fence[pivot];
        int height = fence[pivot];
        while( begin < lo || hi < end-1 )
        {
            if (hi < end-1 && (lo == begin || fence[lo-1] < fence[hi+1]))
            {
                hi++;
                height = min(height, fence[hi]);
            }
            else
            {
                lo--;
                height = min(height, fence[lo]);
            }
            ret = max(ret, height * (hi-lo+1));
            //cerr << '\t' << lo << "~" << hi << " = " << height*(hi-lo+1) << "  \t(pivot=" << pivot << ")\n";
        }
        return ret;
    }());

    return ret;
}
