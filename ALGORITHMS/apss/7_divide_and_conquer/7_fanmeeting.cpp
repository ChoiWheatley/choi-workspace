/*
    link: https://algospot.com/judge/problem/read/FANMEETING
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<bitset>
#include<cmath>
#include<cstdio>
#include<unistd.h>
using namespace std;

constexpr int MAXNUM=200000;

int count_hug(bitset<MAXNUM>& idol, const bitset<MAXNUM>& fan, int idol_num, int fan_num);

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int c;
    cin >> c;
    cin.get();
    while(c-->0)
    {
        bitset<MAXNUM> idol{0};
        bitset<MAXNUM> fan{0};
        int idol_num, fan_num;
        char c;
        for (idol_num=0; (c=cin.get())!='\n'; idol_num++)
        {
            if (c=='M')
                idol[idol_num]=1;
            else
                idol[idol_num]=0;
        }
        for (fan_num=0; (c=cin.get())!='\n'; fan_num++)
        {
            if (c=='M')
                fan[fan_num]=1;
            else
                fan[fan_num]=0;
        }
//        cerr<<"idol="<< idol <<" fan="<< fan <<'\n';
        cout<< count_hug(idol, fan, idol_num, fan_num) << '\n';
    }

    return 0;
}
int count_hug(bitset<MAXNUM>& idol, const bitset<MAXNUM>& fan, int idol_num, int fan_num)
{
    int hug_count = 0;
    for (int i=0; i<=(fan_num-idol_num); i++)
    {
        if ( (idol&fan).none() )
            hug_count++;
        idol<<=1;
//        cerr<<"\tidol="<< idol <<" fan="<< fan <<'\n';
    }
    return hug_count;
}
