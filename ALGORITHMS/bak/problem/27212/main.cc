#include "solution.hpp"
#include <ios>
#include <iostream>

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  usize n, m, c;
  cin >> n >> m >> c;

  vector<vector<i64>> w(c);
  vector<usize> a(n);
  vector<usize> b(m);

  for (auto &row : w) {
    row.resize(c);
  }

  for (usize i = 0; i < c; ++i) {
    for (usize j = 0; j < c; ++j) {
      cin >> w[i][j];
    }
  }

  for (usize i = 0; i < n; ++i) {
    cin >> a[i];
  }
  for (usize i = 0; i < m; ++i) {
    cin >> b[i];
  }

  a = normalize_list(std::move(a));
  b = normalize_list(std::move(b));

  auto submit = solution(w, a, b);

  cout << submit << "\n";

  return 0;
}