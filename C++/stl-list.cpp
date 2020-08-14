#include <iostream>
#include <list>
#include <iterator>
using namespace std;

int main() {
    list<int> l(10, 0);
    l.push_back(1);
    l.push_back(2);
    l.push_front(-1);
    l.push_front(-2);

    copy(l.begin(), l.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    cout << " (*l.begin()) + 2 은 begin 다음 다음 값을 참조하고 * 참조로 값을 꺼내온다 : ";
    cout << (*l.begin()) + 2 << endl;

    cout << "iterator로 직접 순회 : ";
    for (auto l_iter = l.begin(); l_iter != l.end(); l_iter++) {
        cout << *l_iter << ' ';
    }
    cout << endl;

    return 0;
}