#include <iostream>
#include <ios>
#include <vector>
#include <algorithm>

using namespace std;
using isize = long;

inline bool solution(vector<int> && juan, vector<int> && boss) {

  auto const N = juan.size();

  std::sort(juan.begin(), juan.end());
  std::sort(boss.begin(), boss.end());

  auto ju = juan.begin();
  auto bo = boss.begin();

  while (bo != boss.end()) {
    if (*ju < *bo) {
      std::advance(ju, 1);
      std::advance(bo, 1);
    } else {
      std::advance(bo, 1);
    }
    if (std::distance(juan.begin(), ju) >=  isize(N + 1) / 2) {
      return true;
    }
  }

  return false;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> juan(n);
  vector<int> boss(n);

  for (int i = 0; i < n; ++i) {
    cin >> juan[i];
  }

  for (int i = 0; i < n; ++i) {
    cin >> boss[i];
  }

  bool submit = solution(std::move(juan), std::move(boss));

  cout << (submit ? "YES" : "NO") << "\n";
  
  return 0;
}
