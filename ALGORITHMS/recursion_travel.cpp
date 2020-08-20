/*
 * 0부터 차례로 번호가 매겨진 n개의 원소 중 네 개를 고르는
 * 모든 경우의 수를 출력하시오 (n >= 4)
 * n = 7인 경우
 * (0, 1, 2, 3), (0, 1, 2, 4), (0, 1, 2, 5) ...
 * (3, 4, 5, 6)
 * 
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int recur_cnt = 0;
int stupid_cnt = 0;

string stupid_pick(int n)
{
    if (n < 4) return 0;
    string ret = "(";
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            for (int q = j+1; q < n; q++) {
                for (int r = q+1; r < n; r++) {
                    
                    // ret += to_string(i) + ",";
                    // ret += to_string(j) + ",";
                    // ret += to_string(q) + ",";
                    // ret += to_string(r) + "), (";
                    if (++stupid_cnt % 10 == 0) {
                        // ret = ret.substr(0, ret.size() - 3);
                        // ret += "\n(";
                    }
                }
            }
        }
    }
    //ret = ret.substr(0, ret.size() - 3);
    ret += "total count : " + to_string(stupid_cnt);

    return ret;
}
void print_pick(vector<int>& picked) {
    static int cnt = 0;
    string out = "(";
    for (int i = 0; i < picked.size(); i++) {
        out += to_string(picked[i]) + ",";
    }
    out = out.substr(0, out.size() - 1);
    out += ") ";
    if (++cnt % 10 == 0) {
        out += "\n";
    }
    cout << out;
}
void recur_pick(int n, vector<int>& picked, int toPick) {
    int min = 0;
    if (toPick == 0) {
        print_pick(picked);
        return;
    }
    if (!picked.empty()){
        min = picked[picked.size() - 1] + 1;
    }
    for (int i = min; i < n; i++) {
        picked.push_back(i);
        recur_pick(n, picked, toPick - 1);
        picked.pop_back();
    }
}
int main() {
    int input = 10;
    cout << "n = " << input << endl;

    vector<int> picked(0);
    recur_pick(input, picked, 4);



    return 0;
}