#include "solution.hpp"

#include <cstddef>
#include <ios>
#include <iostream>
#include <vector>

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t, w;
  cin >> t >> w;

  vector<int> schedule(size_t(t), 0);
  for (int i = 0; i < t; ++i) {
    cin >> schedule[i];
    schedule[i] -= 1; // 나무 번호가 1번부터 시작하기 때문.
  }

  int submit = solution(schedule, w);

  cout << submit << "\n";

  return 0;
}