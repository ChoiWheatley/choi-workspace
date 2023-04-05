#include <array>
#include <cstddef>
#include <ios>
#include <iostream>
#include <limits>
#include <stdexcept>

using namespace std;
using std::array;
using u32 = unsigned int;

constexpr size_t MAX_N = 100;
constexpr u32 INF = numeric_limits<u32>::max();

using Arr = array<array<u32, MAX_N + 1>, MAX_N + 1>;

Arr g_dist;

/**
@breif: initialize with INFs, except for (i,i) components with 0
*/
inline void init_d() {
  for (auto &line : g_dist) {
    line.fill(INF);
  }
  for (size_t i = 0; i < MAX_N; ++i) {
    g_dist[i][i] = 0;
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  // Initialize d
  init_d();
  size_t n, m;
  cin >> n >> m;
  for (size_t _i = 1; _i <= m; ++_i) {
    size_t i, j;
    u32 weight;
    cin >> i >> j >> weight;
    g_dist[i][j] = std::min(g_dist[i][j], weight);
  }

  for (size_t k = 1; k <= n; ++k) {     // via
    for (size_t i = 1; i <= n; ++i) {   // from
      for (size_t j = 1; j <= n; ++j) { // to
        auto ik = g_dist[i][k];
        auto kj = g_dist[k][j];
        if (i == j || ik >= INF - kj) {
          continue;
        }
        g_dist[i][j] = std::min(g_dist[i][j], ik + kj);
      }
    }
  }

  for (size_t i = 1; i <= n; ++i) {
    for (size_t j = 1; j <= n; ++j) {
      auto get = g_dist[i][j];
      if (get == INF) {
        get = 0;
      }
      cout << get << ' ';
    }
    cout << "\n";
  }

  return 0;
}