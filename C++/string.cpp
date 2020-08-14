#include <iostream>
using namespace std;

int main() {
    string str1 = "C++ is Cool!";
    string str2 = str1;
    string str3 = str2 + " And Clear!";
    string str4 = "안녕하세요";

    cout << str3 + "의 길이는 " + to_string(str3.length()) + " 입니다." << endl;
    cout << str4 + "의 크기는 " + to_string(str4.size()) + " 입니다." << endl;



    return 0;
}