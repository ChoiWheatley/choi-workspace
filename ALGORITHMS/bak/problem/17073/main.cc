#include <algorithm>
#include <cstddef>
#include <ios>
#include <iostream>
#include <string>
#include <tuple>

using namespace std;
constexpr size_t MAX_N = 500'000;
int g_count[MAX_N + 1];

int main(void) {
  std::fill(g_count, g_count + MAX_N + 1, 0);
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, w;
  cin >> n >> w;

  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    if (g_count[u] < 2)
      g_count[u] += 1;
    if (g_count[v] < 2)
      g_count[v] += 1;
  }

  double count = 0;
  for (size_t i = 2; i <= MAX_N; ++i) {
    if (g_count[i] == 1) {
      count += 1;
    }
  }

  double answer = w / count;
  cout.precision(6); // coerce into 6-digit point, not scientific one
  cout << std::fixed << answer << "\n";
  return 0;
}