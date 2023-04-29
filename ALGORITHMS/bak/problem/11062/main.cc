#include "solution.hpp"
#include <ios>
#include <iostream>
#include <vector>

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;

  for (int tc = 0; tc < t; ++tc) {
    int n;
    cin >> n;
    vector<Score> d(n);
    for (int i = 0; i < n; ++i) {
      cin >> d[i];
    }
    Score submit = solution(d);
    cout << submit << "\n";
  }

  return 0;
}