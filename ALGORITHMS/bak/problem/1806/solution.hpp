#include <algorithm>
#include <vector>

#define cr const &

using std::vector;
using i64 = long long;
using Vec = vector<i64>;

template <typename T, class Fn> inline T first_true(T begin, T end, Fn pred) {
  auto l = begin;
  auto r = end;
  while (l < r) {
    auto m = l + (r - l) / 2;
    if (pred(m)) {
      // move left, next range is [l, m)
      r = m;
    } else {
      // move right, next range is [m + 1, r)
      l = m + 1;
    }
  }
  return l;
}

/**
@param:
- from: inclusive
- to: exclusive
*/
inline i64 sum_between(Vec cr sum, size_t from, size_t to) {
  if (to == 0) {
    return sum[0];
  }
  if (from == 0) {
    return sum[to - 1];
  }
  return sum[to - 1] - sum[from - 1];
}

/**
@brief: Parametric search

find minimum of len(H) where sum(H) >= S

if f(l) is true where l is len(H) that satisfy upper condition, then
 l, l + 1, ... will also true

@param:
- sum: assume the sequence is `partial_sum`ed
- S: given condition
*/
inline size_t solution(Vec &&sum, i64 S) {
  if (sum[0] >= S) {
    // corner case: single element >= S
    return 1;
  }
  for (size_t i = 1; i < sum.size(); ++i) {
    // corner case: single element >= S
    auto elem = sum[i] - sum[i - 1];
    if (elem >= S) {
      return 1;
    }
  }
  auto ret = first_true(size_t(0), sum.size(), [&sum, S](auto length) {
    for (size_t from = 0; from <= sum.size() - length; ++from) {
      size_t to = from + length;
      if (sum_between(sum, from, to) >= S) {
        return true;
      }
    }
    return false;
  });
  if (ret >= sum.size() && sum.back() < S) {
    return 0;
  }
  return ret;
}