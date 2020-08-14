#include <iostream>
#include <deque>
#include <iterator>
using namespace std;

int main() {
    deque<int> d(10, 0);
    d.push_back(1);
    d.push_front(-1);
    copy(d.begin(), d.end(), ostream_iterator<int>(cout, " "));  //iterator 공부를 안하고 왔더니 그만..
    cout << endl;

    return 0;
}