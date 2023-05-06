#include <array>
#include <iterator>
#include <numeric>
#include <vector>

#define cr const &

using i64 = long long;
using isize = long long;
using usize = unsigned long long;

constexpr usize MAX_K = 500;
constexpr i64 MAX = ~(i64(1) << 63);

using Vec = std::vector<i64>;
using DpArr = std::array<std::array<i64, MAX_K>, MAX_K>;

DpArr dp_global;

static auto sum_between(Vec cr sum, usize i, usize j) -> i64 {
  if (i == 0) {
    return sum[j];
  }
  return sum[j] - sum[i - 1];
}

/**
 * @brief non-recursive dynamic programming
 */
static auto solution(Vec cr k) -> i64 {
  auto const K = k.size();
  auto &dp = dp_global;
  // init dp array
  for (auto &row : dp) {
    row.fill(0);
  }

  Vec my_sum;
  std::partial_sum(k.cbegin(), k.cend(), std::back_inserter(my_sum));

  // length = 0인 모든 dp[i][i]에 대하여 0이다. 따라서 pass

  // length = 1인 모든 dp[i][i+1]에 대하여 k[i] + k[i+1]이다.
  usize length = 1;
  for (usize left = 0; left < K - length; ++left) {
    usize right = left + length;
    dp[left][right] = k[left] + k[right];
  }

  // length >= 2인 모든 dp[i][j]에 대하여 다음 식을 만족한다.
  /*
   dp[i][j] = sum[i:j] + min(
   for l in range(i, j):
       dp[i][l] + dp[l+1][j])
  */
  for (usize length = 2; length < K + 1; ++length) {
    for (usize left = 0; left < K - length; ++left) {
      usize right = left + length;

      i64 best = MAX;
      for (usize mid = left; mid < right; ++mid) {
        best = std::min(best, dp[left][mid] + dp[mid + 1][right]);
      }

      dp[left][right] = sum_between(my_sum, left, right) + best;
    }
  }

  return dp[0][K - 1];
}