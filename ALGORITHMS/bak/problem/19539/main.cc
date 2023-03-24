#include "solution.hpp"
#include <ios>
#include <iostream>
#include <vector>

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  auto trees = vector<int>(size_t(n));
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    cin >> trees[i];
    sum += trees[i] % 3;
  }

  if (sum % 3 != 0) {
    cout << "NO\n";
  } else {
    bool submit = solution(trees);
    cout << (submit ? "YES" : "NO") << "\n";
  }

  return 0;
}