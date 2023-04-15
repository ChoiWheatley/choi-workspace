#include "solution.hpp"
#include <ios>
#include <iostream>

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  size_t k;
  cin >> n >> k;

  auto ls = Vec(n);
  for (size_t i = 0; i < n; ++i) {
    cin >> ls[i];
  }

  auto answer = solution(std::move(ls), k);

  cout << answer << "\n";

  return 0;
}