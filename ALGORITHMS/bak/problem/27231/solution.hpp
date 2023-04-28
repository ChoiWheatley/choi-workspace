#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iterator>
#include <math.h>
#include <set>
#include <string>
#include <vector>

#define cr const &

using std::set;
using std::string;
using std::vector;
using Result = int;

constexpr Result INFINITE = -1;

using Set = set<int>;

/**
@brief: do (n-1)Ck
*/
inline vector<vector<int>> comb(int n, int k) {
  n = n - 1;
  vector<bool> bitmask(size_t(k), true);
  bitmask.resize(n, false);
  vector<vector<int>> ret;
  do {
    ret.emplace_back();
    for (int i = 0; i < n; ++i) {
      if (bitmask[i] == true) {
        ret.back().push_back(i);
      }
    }
  } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
  return ret;
}

inline int my_pow(int base, int exp) {
  int sum = 1;
  for (int i = 0; i < exp; ++i) {
    sum *= base;
  }
  return sum;
}

/**
@brief: returns a number which digit only contains [from, to)

@param:
- n: target
- from: inclusive
- to: exclusive

@example:
splice(1234, 1, 2) => 3
splice(1234, 0, 2) => 34
splice(1234, 1, 4) => 123
*/
inline int splice(int n, int from, int to) {
  n %= my_pow(10, to);
  n -= n % my_pow(10, from);
  n /= my_pow(10, from);
  return n;
}

inline int digits_of(int n) {
  return static_cast<int>(std::ceil(std::log10(n)));
}

/**
@brief: if n = 2023, indices = {0, 1, 2}, returns 2+0+2+3

if n = 2023, indices = {0, 1}, returns 20+2+3
*/
inline int to_splitted_sum(int n, vector<int> indices) {
  int ret = 0;
  // normalize
  for (auto &e : indices) {
    e += 1;
  }
  // initial one
  ret += splice(n, 0, indices[0]);
  for (int i = 1; i < int(indices.size()); ++i) {
    ret += splice(n, indices[i - 1], indices[i]);
  }
  // last one
  ret += splice(n, indices.back(), digits_of(n));
  return ret;
}

/**
@brief: making S_n is something like this:::

make_s(2023) =>
  S_n = {2023, 202+3, 20+23, 2+023, 20+2+3, 2+02+3, 2+0+23, 2+0+2+3}
*/
inline Set make_s(int n) {
  int digits = digits_of(n);
  Set ret = {n}; // itself when `number_of_plus` == 0
  for (int number_of_plus = 1; number_of_plus < digits - 1; ++number_of_plus) {
    auto indices = comb(digits, number_of_plus);
    for (auto cr e : indices) {
      ret.insert(to_splitted_sum(n, e));
    }
  }
  return ret;
}

/**
@brief: do every sum of digit's exponent of m
*/
inline int calc_m(int n, int m) {
  int ret = 0;
  auto digits = digits_of(n);
  for (int exp = 1; exp <= digits; ++exp) {
    ret += my_pow(n % 10, m);
    n /= 10;
  }
  return ret;
}

inline Result solution(int n) {
  if (splice(n, digits_of(n), digits_of(n) + 1) == 1 &&
      splice(n, 0, digits_of(n)) == 0) {
    return INFINITE;
  }
  // let's assume there are no `infinite` case
  Set sn = make_s(n);
  int mm = 0;
  int m = 1;
  Result ret = 0;

  do {
    if (sn.find(mm) != sn.end()) {
      ret += 1;
    }
    mm = calc_m(n, m);
    m += 1;
  } while (mm <= n);

  return ret;
}
