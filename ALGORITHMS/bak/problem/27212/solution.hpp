#include <array>
#include <vector>
#define cr const &

using usize = unsigned long long;
using i64 = long long;

constexpr usize C = 16;
constexpr usize MAX_N = 1000;
constexpr usize MAX_M = 1000;

using std::array;
using std::vector;

static array<array<i64, MAX_M>, MAX_N> dp_global;

/**
@brief: DP[i][j]: A 대학의 i번째 학생과 B 대학의 j 이하번째 학생이 악수를 했을
때 얻을 수 있는 최고 만족도를 저장한다.
*/
static inline i64 solution(vector<vector<i64>> cr w, vector<usize> cr a,
                           vector<usize> cr b) {
  const usize N = a.size();
  const usize M = b.size();
  auto &dp = dp_global;
  // init dp each first row and col of the 2d-list
  dp[0][0] = w[a[0]][b[0]];
  for (usize j = 1; j < M; ++j) {
    dp[0][j] = std::max(dp[0][j - 1], w[a[0]][b[j]]);
  }
  for (usize i = 1; i < N; ++i) {
    dp[i][0] = std::max(dp[i - 1][0], w[a[i]][b[0]]);
  }

  // do the real thing, there are three cases
  for (usize i = 1; i < N; ++i) {
    for (usize j = 1; j < M; ++j) {
      // 1. Ai and Bj has handshaked => we can confirm new handshake!
      auto case1 = dp[i - 1][j - 1] + w[a[i]][b[j]];
      // 2. Ai handshaked with noone => just repeat the value from previous row
      auto case2 = dp[i - 1][j];
      // 3. Ai has already handshaked to someone else before Bj-1
      auto case3 = dp[i][j - 1];
      dp[i][j] = std::max(std::max(case1, case2), case3);
    }
  }

  return dp[N - 1][M - 1];
}

static inline vector<usize> normalize_list(vector<usize> &&ls) {
  for (auto &e : ls) {
    e -= 1;
  }
  return ls;
}