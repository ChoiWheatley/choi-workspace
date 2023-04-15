#include "solution.hpp"

using namespace std;
using i64 = long long;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  size_t n;
  cin >> n;
  auto ls = vector<i64>(n);

  for (size_t i = 0; i < n; ++i) {
    cin >> ls[i];
  }

  cout << solution(std::move(ls)) << "\n";

  return 0;
}