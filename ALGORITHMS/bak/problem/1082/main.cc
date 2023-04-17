#include "solution.hpp"
#include <ios>
#include <iostream>

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;

  VecDeque prices(n);
  for (int i = 0; i < n; ++i) {
    cin >> prices[i];
  }

  int m;
  cin >> m;

  auto submit = solution(std::move(prices), m);
  if (submit.empty()) {
    cout << '0' << "\n";
  } else {
    for (int i = int(submit.size()) - 1; i >= 0; --i) {
      cout << submit[i];
    }
    cout << "\n";
  }

  return 0;
}