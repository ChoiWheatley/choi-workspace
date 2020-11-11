/*
 * Chapter8 Exercise2 : print(vector) 함수 만들고 응용하기
 * Ex3 : fibonacci 함수 만들기
 * Ex5 : reverse 함수의 두 가지 버전을 만들기, 하나는 원본 보존 및
 *      결과를 리턴하고, 다른 하나는 원본에 덮어씌우기
 * Ex6 : string에 대해서도 동일한 결과를 만들도록 바꾸기
 */

#include "std_lib_facilities.h"

typedef unsigned long long ULL;

template<typename T>
void print(vector<T>);
void fibonacci(ULL x, ULL y, vector<ULL>& v, int n);
template<typename T>
vector<T> rev_ret(const vector<T>& v);
template<typename T>
void rev(vector<T>& v);
template<typename T>
void swap(T& a, T& b);


//
//
int main()
{
	vector<ULL> fib;
    fibonacci(1, 2, fib, 15);
    print(fib);
    vector<ULL> reversed{rev_ret(fib)};
    print(reversed);
    rev(fib);
    print(fib);

    vector<string> strvec {"a", "b", "c", "d", "e"};
    print(strvec);
    rev(strvec);
    print(strvec);
	
	return 0;
}
//
//
template<typename T>
void print(vector<T> v) 
{
    int cnt = 0;
    for (auto i : v) {
        cout << i << " ";
        if (!(++cnt % 10)) cout << '\n';
    }
    cout << "\n\n";
}
//fib : [x, y, x+y, x+2y, 2x+3y, ... , (n-3)x+(n-2)y] : v
void fibonacci(ULL x, ULL y, vector<ULL>& v, int n)
{
    if (!v.empty()) error("the vector v is not empty!");
    v.push_back(x);
    v.push_back(y);
    for (int i = 2; i < n; i++) {
        v.push_back(v[i-1] + v[i-2]);
    }
}
template<typename T>
vector<T> rev_ret(const vector<T>& v)
{
    vector<T> ret;
    for (int i = v.size()-1; i >= 0; i--) {
        ret.push_back(v[i]);
    }
    return ret;
}
template<typename T>
void rev(vector<T>& v)
{
    for (int i = 0; i <= (v.size()/2); i++) {
        T tmp = v[i];
        v[i] = v[ v.size()-1-i ];
        v[ v.size()-1-i ] = tmp;
    }
}
template<typename T>
void swap(T& a, T& b)
{
    T tmp = a;
    a = b;
    b = a;
}