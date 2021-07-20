#include"apss_7_big_mult_karatsuba.h"
#include"apss_7_big_mult_slow.h"
using namespace std;

int count_hug(vector<int>& idol, vector<int>& fan);
extern vector<int> karatsuba(vector<int>& a, vector<int>& b);
extern void normalize(vector<int>& num);

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
        vector<int> idol;
        vector<int> fan;
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
//        cerr<<"idol="<< idol <<" fan="<< fan <<'\n';
        cout<< count_hug(idol, fan) << '\n';
    }

    return 0;
}

int count_hug(vector<int>& idol, vector<int>& fan)
{
    // 자리를 뒤집어야 한다. 현재 idol 과 fan은 서로 맞은편을 곱하는 것이 아닌,
    // (idol.size()-i , i) 가 서로 마주보고 있는 상황이다. 일반적인 곱하기
    // 상황과는 정 반대이기 때문에 곱해줄 때에도 반대로 뒤집어 주어야 한다.
    vector<int> idol_{idol.rbegin(), idol.rend()};


	// karatsuba 알고리즘 안에 자리올림 (normalize)가 들어있어서 틀린 값을
	// 얻어낸다. 이걸 제거한 버전으로 다시 시도해 보아야 한다.
	vector<int> mult = karatsuba(idol_, fan);

//    cout << "on " << __func__ << ",\t";
//    for (int i=mult.size()-1; i >= 0; --i)
//    {
//        cout << mult[i] << ' ';
//    }
//    cout <<'\n';

	int ret = 0;
    for (size_t i=idol.size()-1; i < fan.size(); i++)
	{
		if (mult[i]==0)
			ret++;
	}
	return ret;
}
