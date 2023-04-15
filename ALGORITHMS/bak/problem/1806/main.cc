#include "solution.hpp"
#include <ios>
#include <iostream>
#include <vector>

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  size_t n;
  i64 s;
  cin >> n >> s;

  Vec seq(n);
  cin >> seq[0];
  for (size_t i = 1; i < n; ++i) {
    cin >> seq[i];
    seq[i] += seq[i - 1]; // cumulative sum
  }

  auto submit = solution(std::move(seq), s);
  cout << submit << "\n";

  return 0;
}