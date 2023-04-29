#include <algorithm>
#include <array>
#include <iterator>
#include <numeric>
#include <vector>
#define cr const &
using std::array;
using std::max;
using std::vector;

using Score = int;
using Idx = int;

constexpr int MAX_N = 1001;
using Arr = array<array<Score, MAX_N>, MAX_N>;

static inline Score sum_of(vector<Score> cr sum, Idx k, Idx j) {
  if (k == 0) {
    return sum[j];
  }
  return sum[j] - sum[k - 1];
}

/**
@param:
- k: inclusive begin
- j: inclusive end
*/
static inline Score sol_recur(Arr &dp, vector<Score> cr cards,
                              vector<Score> cr sum, Idx k, Idx j) {
  if (dp[k][j] != 0) {
    goto FAST_RETURN;
  }
  if (k == j) {
    dp[k][j] = cards[k];
    goto FAST_RETURN;
  }
  if (k + 1 == j) {
    dp[k][j] = max(cards[k], cards[j]);
    goto FAST_RETURN;
  }
  dp[k][j] = max(
      cards[k] + sum_of(sum, k + 1, j) - sol_recur(dp, cards, sum, k + 1, j),
      cards[j] + sum_of(sum, k, j - 1) - sol_recur(dp, cards, sum, k, j - 1));

FAST_RETURN:
  return dp[k][j];
}

/**
@brief: Player "G" always take the card first, and then player "M"
interchangely. Given that two players play to get best score, find out the score
of player "G" and "M"

@idea: DP[k, j] = max {
  c[k] + c[k+1:j].sum - DP[k+1, j],
  c[j] + c[k:j-1].sum - DP[k, j-1]
}
*/
inline Score solution(vector<Score> cr cards) {
  vector<Score> sum;
  std::partial_sum(cards.cbegin(), cards.cend(), std::back_inserter(sum));

  Arr dp;
  for (auto &line : dp) {
    line.fill(0);
  }

  return sol_recur(dp, cards, sum, 0, Idx(cards.size() - 1));
}