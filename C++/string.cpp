#include <iostream>
#include <string>
#include <locale>
using namespace std;

int main() {
    wcin.imbue(locale("ko-KR"));
    wcout.imbue(locale("ko-KR"));
    wstring address, name;
    wcout << L"자신의 이름을 입력해주세요 :";
    getline(wcin, name);
    wcout << L"자신이 살고 있는 도시를 입력해주세요 :";
    getline(wcin, address);

    wcout << address << L"에 살고있는 " << name << L"씨 맞으십니까?" << endl;
    wcout << L"당신의 이름은 총 " << to_wstring(name.size()) << L"글자 이군요! 놀라워요" << endl;
    for (int i = 0; i < name.size(); i++) {
        wcout << name[i] << " ";
    }
    wcout << endl;
    


    return 0;
}