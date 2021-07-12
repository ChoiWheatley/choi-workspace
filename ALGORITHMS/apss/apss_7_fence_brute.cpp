#include<iostream>
#include<vector>
#include<unistd.h>
#include<algorithm>
using namespace std;

#define MAX_FENCE 20000
vector<int> fence;

int solve();

int main(void)
{
    int c, n;
    cin >> c;
    while(c-->0)
    {
        cin >> n;
        fence = vector<int>(n);
        for (int i = 0; i < n; i++)
        {
            cin >> fence[i];
        }
        cout << solve() << '\n';
    }
    return 0;
}

int solve()
{
    int ret = 0;
    for (int left = 0; left < fence.size(); left++)
    {
        int height = fence[left];
        for (int right = left; right < fence.size(); right++)
        {
            int width = right - left + 1;
            height = min(height, fence[right]);
            ret = max(ret, width * height);
        }
    }
    return ret;
}
