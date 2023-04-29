#include "solution.hpp"
#include <deque>
#include <ios>
#include <iostream>

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;

  for (int tc = 0; tc < t; ++tc) {
    int n;
    cin >> n;
    deque<Card> d(n);
    for (int i = 0; i < n; ++i) {
      cin >> d[i];
    }
    Result submit = solution(move(d));
    cout << submit.first << "\n";
  }

  return 0;
}