#include"apss_7_big_mult_karatsuba.h"
#include"apss_7_big_mult_slow.h"
using namespace std;

int count_hug(vector<char>& idol, vector<char>& fan);
extern vector<char> karatsuba(vector<char>& a, vector<char>& b);

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
        vector<char> idol;
        vector<char> fan;
        int idol_num, fan_num;
        char c;
        for (idol_num=0; (c=cin.get())!='\n'; idol_num++)
        {
            if (c=='M')
				idol.push_back(1);
            else
                idol.push_back(0);
        }
        for (fan_num=0; (c=cin.get())!='\n'; fan_num++)
        {
            if (c=='M')
				fan.push_back(1);
            else
				fan.push_back(0);
        }
        cerr<<"idol="<< idol <<" fan="<< fan <<'\n';
        cout<< count_hug(idol, fan) << '\n';
    }

    return 0;
}

int count_hug(vector<char>& idol, vector<char>& fan)
{
	// karatsuba 알고리즘 안에 자리올림 (normalize)가 들어있어서 틀린 값을
	// 얻어낸다. 이걸 제거한 버전으로 다시 시도해 보아야 한다.
	vector<char> mult = karatsuba(idol, fan);
	int ret = 0;
	for (int i=idol.size()-1; i<fan.size(); i++)
	{
		if (mult[i]==0)
			ret++;
	}
	return ret;
}
