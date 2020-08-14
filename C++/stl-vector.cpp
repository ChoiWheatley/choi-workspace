#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
using namespace std;

int main() {
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.pop_back();   //pop_back() 함수는 리턴을 하지 않는다.

    cout << "순회 - [] 오퍼레이터로 배열처럼 접근 : " << endl;
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << ' ';
    }
    cout << endl;

    cout << "순회 - ranged_for 문으로 iterator로 하여금 순회 : " << endl;
    for (auto vn : v) {
        cout << vn << ' ';
    }
    cout << endl;

    cout << "순회 - for_each 문으로 람다함수로 하여금 순회 : " << endl;
    for_each(v.begin(), v.end(), [&](auto n) {
        n = 1;      // 람다함수의 인자 n 은 int&형이었나?
        cout << n << ' ';
    });
    cout << endl;

    //2차원 벡터
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 99);
    vector<int> vec2(10, 0);
    vector<vector<int>> vec(10, vec2);
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[i].size(); j++) {
            vec[i][j] = dis(gen);
        }
    }
    /*
    ranged-for 문에서 돌아가는 iterator는 읽기만 가능하네...
    for (auto n : vec) {
        for (auto nn : n) {
            nn = dis(gen);
        }
    }
    */

    cout << "2차원 vector에 랜덤값을 넣고 ranged_for 문으로 iterator로 하여금 순회 : " << endl;
    for (auto n : vec) {
        for (auto nn : n) {
            cout << nn << ' ';
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}