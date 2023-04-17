#include <algorithm>
#include <deque>
#include <string>
#include <vector>

#define cr const &

struct Point {
  int index;
  int *price_ptr;
  explicit Point(int index, int *price_ptr)
      : index(index), price_ptr(price_ptr) {}
};

inline bool operator<(Point cr lhs, Point cr rhs) {
  if (*lhs.price_ptr == *rhs.price_ptr) {
    // NOTICE: index is reversed order
    return lhs.index > rhs.index;
  }
  return *lhs.price_ptr < *rhs.price_ptr;
}

using namespace std;
using VecDeque = deque<int>;

/**
@return: i-th element == coefficient 10^i, last element is not 0 if size is not
1

@solution:
1. let `a` as the most cheap number-tag in range 1..n
2. let `b` as the most cheap number-tag in range 0..n, which can be same as a or
0
3. try buy one `a` and buy `b` with left of money.
   result will be "abb...bb"
4. from x as n..a (in a reversed order), try replace our highest number-tag into
x if affordable.
5. from x as n..b (in a reversed order), try replace other number-tags into x if
affordable.
6. PROFIT 💸
*/
inline VecDeque solution(VecDeque &&prices, int m) {
  if (prices.size() <= 1) {
    return {};
  }
  const auto n = int(prices.size());
  int a, b;
  a = 1; // we can assure `prices` are at least have two elements
  b = 0;
  // 1. 2.
  for (int i = 2; i < n; ++i) {
    if (prices[i] <= prices[a]) {
      a = i;
    }
    if (prices[i] <= prices[b]) {
      b = i;
    }
  }

  VecDeque result;

  // 3.
  if (m >= prices[a]) {
    result.push_front(a);
    m -= prices[a];
  } else {
    // corner case: there are only zeros!!!!!! 🙀
    return {};
  }
  while (m >= prices[b]) {
    result.push_front(b);
    m -= prices[b];
  }

  // 4.
  for (int i = n - 1; i > a; --i) {
    int delta_price = prices[i] - prices[a];
    if (m >= delta_price) {
      // replace `a` with new number-tag
      result.back() = i;
      m -= delta_price;
    }
  }

  // 5.
  for_each(next(result.rbegin()), result.rend(), [&](auto &digit) {
    for (int i = n - 1; i > b; --i) {
      int delta_price = prices[i] - prices[b];
      if (m >= delta_price) {
        // replace `b` with new number-tag
        digit = i;
        m -= delta_price;
      }
    }
  });

  return result;
}
