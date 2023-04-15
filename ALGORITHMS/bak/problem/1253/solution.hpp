#include <algorithm>
#include <bitset>
#include <cstddef>
#include <ios>
#include <iostream>
#include <iterator>
#include <vector>

#define cr const &

using namespace std;
using i64 = long long;

constexpr size_t N = 2000;

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

inline size_t solution(vector<i64> &&ls) {
  auto const n = ls.size();
  auto visited = bitset<N + 1>();

  std::sort(ls.begin(), ls.end());

  size_t count = 0;

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i + 1; j < n; ++j) {
      auto sum = ls[i] + ls[j];

      auto lb = first_true(ls.begin(), ls.end(),
                           [sum](auto x) { return (*x) >= sum; });
      auto ub = first_true(ls.begin(), ls.end(),
                           [sum](auto x) { return (*x) > sum; });

      for (auto itr = lb; itr != ub; ++itr) {
        auto index = std::distance(ls.begin(), itr);
        if (index != i && index != j && (*itr) == sum && !visited[index]) {
          visited.set(index);
          count += 1;
        }
      }
    }
  }

  return count;
}