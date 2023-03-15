#include "solution.hpp"
#include <cstddef>
#include <ios>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::ios;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  i64 n;
  i64 s;
  i64 m;
  cin >> n >> s >> m;

  using std::vector;
  auto tte = vector<i64>(size_t(m));
  for (size_t idx = 0; idx < m; ++idx) {
    cin >> tte[idx];
  }

  auto submit = solution(tte, n - s);

  cout << submit + 1 << "\n";

  return 0;
}