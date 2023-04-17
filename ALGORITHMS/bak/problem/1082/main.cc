#include "solution.hpp"
#include <ios>
#include <iostream>

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

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
    cout << '0';
  } else {
    for_each(submit.crbegin(), submit.crend(),
             [](auto cr elem) { cout << elem; });
  }
  cout << "\n";

  return 0;
}