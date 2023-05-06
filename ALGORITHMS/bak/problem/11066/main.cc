#include "solution.hpp"
#include <ios>
#include <iostream>

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  usize T;
  cin >> T;
  for (usize tc = 0; tc < T; ++tc) {
    i64 K;
    cin >> K;
    Vec k(K);
    for (usize i = 0; i < K; ++i) {
      cin >> k[i];
    }

    i64 submit = solution(k);
    cout << submit << "\n";
  }

  return 0;
}