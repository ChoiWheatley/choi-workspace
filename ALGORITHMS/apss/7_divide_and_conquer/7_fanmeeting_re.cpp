using namespace std;

#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<cmath>
#include<cstdlib>
#include<sys/types.h>

/*
    카라츠바의 빠른 곱셈 알고리즘을 시작하기에 앞서, 
    일반적으로 곱셈을 수행하는 방식을 그대로 코드에 적용
    시켜보자.
*/

using namespace std;

//vector<char> slow_mult(const vector<int>& a, const vector<int>& b);
//void normalize(vector<int>& num);
//
//   int main(void)
//   {
//       vector<char> a{4,3,2,1};
//       vector<char> b{8,7,6,5};
//       vector<char> ret = slow_mult(a, b);
//       for (int i = ret.size()-1; i >= 0; --i)
//       {
//           cout << static_cast<int>(ret[i]) << ' ';
//       }
//       printf("\n");
//       return 0;
//   }
// two vectors index is equal to power of 10
// a[i] means a's i'th digit. (==a[i] * 10^i)
vector<int> slow_mult(const vector<int>& a, const vector<int>& b)
{
    vector<int> ret( a.size() + b.size() );
    fill(ret.begin(), ret.end(), 0);
    // do multiply each indices
    for (size_t i = 0; i < a.size(); i++)
    {
        for (size_t j = 0; j < b.size(); j++)
        {
            ret[i+j] += a[i] * b[j];
        }
    }

    // when simple multiply is over,
    // you should NORMALIZE this, 
    // because each index might bigger than 10
//    normalize(ret);

    return ret;
}
// 자릿수 올림을 처리
void normalize(vector<int>& num)
{
    num.push_back(0);
    for (size_t i = 0; i < num.size(); i++)
    {
        if (num[i] < 0)
        {
            char borrow = static_cast<int>((abs((num[i])) + 9) / 10);
            num[i+1] -= borrow;
            num[i] += borrow * 10;
        }
        else
        {
            num[i+1] += num[i] / 10;
            num[i] %= 10;
        }
    }
    while(num.size() > 1 && num.back() == 0) num.pop_back();
}

extern void normalize(vector<int>& num);
extern vector<int> slow_mult(const vector<int>& a, const vector<int>& b);

vector<int> karatsuba(vector<int>& a, vector<int>& b);
// helper functions
vector<int> operator+(const vector<int>& a, const vector<int>& b);
vector<int> operator-(const vector<int>& a, const vector<int>& b);
vector<int> operator*(vector<int>& a, vector<int>& b);
bool operator<(const vector<int>& a, const vector<int>& b);
bool operator>(const vector<int>& a, const vector<int>& b) {return !(a<b);}
vector<int> pow10(const vector<int>& a, int amt);
istream& operator>>(istream& ist, vector<int>& a);
ostream& operator<<(ostream& os, const vector<int>& a);

vector<int> karatsuba(vector<int>& a, vector<int>& b)
{
    int an = a.size(), bn = b.size();
    if (an < bn) 
        return karatsuba(b, a);
    // base condition : a 또는 b가 비어있는 경우
    if (an == 0 || bn == 0) 
        return vector<int>();
    // base condition : a 가 비교적 짧은 경우, 일반 mult로 해결한다.
    if (bn < 5) 
        return slow_mult(a, b);

    // a, b를 half 자리와 그 나머지로 분리한다.
    int half = an / 2;
    vector<int> a0 {a.begin(), a.begin()+half};
    vector<int> a1 {a.begin()+half, a.end()};
    vector<int> b0 {b.begin(), b.begin() + min(b.size(), (size_t)half)};
    vector<int> b1 {b.begin() + min(b.size(), (size_t)half), b.end()};

//    cerr << "a0=" << a0 << ", a1=" << a1 << '\n';
//    cerr << "b0=" << b0 << ", b1=" << b1 << '\n';

    // a * b == z0 + z1*pow(10,half) + z2*pow(10, half+half) 이때,
    // z0 = a0 * b0
    // z2 = a1 * b1
    // z1 = (a1*b0 + a0*b1) OR ( (a0+a1)*(b0+b1) - z0 - z2 )
    vector<int> z0 = karatsuba(a0, b0);
    vector<int> z2 = karatsuba(a1, b1);

    a0 = a0 + a1;
    b0 = b0 + b1;
    vector<int> z1 = karatsuba(a0, b0) - z0 - z2;
    z1 = pow10(z1, half);
    z2 = pow10(z2, half+half);

    vector<int> ret(0);
    ret = ret + z0 + z1 + z2;
    return ret;
}
vector<int> operator+(const vector<int>& a, const vector<int>& b)
{
    if (a < b) return operator+(b, a);

    vector<int> ret(a);
    for (size_t i = 0; i < b.size(); i++)
    {
        ret[i] += b[i];
    }

//    normalize(ret);
    return ret;
}
vector<int> operator-(const vector<int>& a, const vector<int>& b)
{
    if (a < b) return operator-(b, a);

    vector<int> ret(a);
    for (size_t i = 0; i < b.size(); i++)
    {
        ret[i] -= b[i];
    }
    
//    normalize(ret);
    return ret;
}
vector<int> operator*(vector<int>& a, vector<int>& b)
{
    // karatsuba
    vector<int> ret = karatsuba(a, b);
    
    // normalize
    normalize(ret);
    return ret;
}
vector<int> pow10(const vector<int>& a, int amt)
{
    vector<int> ret{a};
    ret.insert(ret.begin(), amt, 0);
    return ret;
}
// "1234567890" -> [0,9,8,7,6,5,4,3,2,1]
istream& operator>>(istream& ist, vector<int>& a)
{
    char c;
    while ((c = ist.get()))
    {
        if (c == '\n') break;
        a.insert(a.begin(), atoi(&c));
    }
    return ist;
}
// [0,9,8,7,6,5,4,3,2,1] -> "1234567890"
ostream& operator<<(ostream& os, const vector<int>& a)
{
    for (int i = a.size()-1; i >= 0; --i)
    {
        os << (int)a[i] ;
    }
    return os;
}
bool operator<(const vector<int>& a, const vector<int>& b)
{
    if (a.size() < b.size()) return true;
    if (a.size() > b.size()) return false;

    for (int i = a.size()-1; i >= 0; --i)
    {
        if (a[i] < b[i]) return true;
        if (a[i] > b[i]) return false;
    }
    return false;
}
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
