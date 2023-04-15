#include <algorithm>
#include <cstdint>
#include <iterator>
#include <vector>

#define cr const &

using std::vector;
using Vec = vector<int>;

constexpr size_t INV = (1 << 30) - 1;

inline bool is_rainbow(Vec cr sequence) {
  return std::all_of(sequence.begin(), sequence.end(),
                     [](auto e) { return e > 0; });
}

template <typename Iter> inline bool try_advance(Iter end, Iter &dst) {
  if (std::next(dst) != end) {
    std::advance(dst, 1);
    return true;
  }
  return false;
}

/**
@brief: two pointers

The problem gurantees that given sequence has at least one
point which is colored with `i` where 0 <= i < k

*/
inline size_t solution(Vec &&ls, size_t k) {
  const auto BEGIN = ls.begin();
  const auto END = ls.end();
  for (auto &e : ls) {
    e -= 1; // normalize
  }
  // initial registration of sequences,
  // b_inner starts in range [0, 0), which is empty and
  // b_outer starts in range [0, n), which has all
  auto b_outer = Vec(k);
  auto b_inner = Vec(k);
  for (auto cr e : ls) {
    b_outer[e] += 1;
  }

  size_t ret = INV;
  auto lo = BEGIN;
  auto hi = lo;

  while (lo != END && hi != END) {
    if (is_rainbow(b_inner)) {
      if (is_rainbow(b_outer)) {
        // @@@@@@ DOUBLE RAINBOW @@@@@@
        auto len = std::distance(lo, hi);
        ret = std::min(ret, size_t(len));
        // Because much shorter answer might exists, keep going through
        // with advancing `lo` iterator
        b_inner[*lo] -= 1;
        b_outer[*lo] += 1;
        if (!try_advance(END, lo)) {
          goto EARLY_RETURN;
        }
      } else {
        // feed b_outer with advancing `lo` iterator
        b_inner[*lo] -= 1;
        b_outer[*lo] += 1;
        if (!try_advance(END, lo)) {
          goto EARLY_RETURN;
        }
      }
    } else {
      // no rainbow found, feed `b_inner` with advancing `hi` iterator
      b_inner[*hi] += 1;
      b_outer[*hi] -= 1;
      if (!try_advance(END, hi)) {
        goto EARLY_RETURN;
      }
    }
  }

EARLY_RETURN:

  if (ret == INV) {
    // no double rainbow found
    return 0;
  }
  return ret;
}