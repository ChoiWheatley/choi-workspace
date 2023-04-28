#include <algorithm>
#include <math.h>
#include <set>

#define cr const &

using std::set;
using Result = int;

constexpr Result INFINITE = -1;

using Set = set<int>;

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
@brief: split integer just like string::substr in std

@usage:
- split_int(2023, 0) => {2023}, {}
- split_int(2023, 1) => {202}, {3}
- split_int(2023, 2) => {20}, {23}
- split_int(2023, 3) => {2}, {23}
*/
inline std::pair<int, int> split_int(int n, int digit) {
  if (n == 0) {
    return std::make_pair(n, 0);
  }
  int pow_result = my_pow(10, digit);
  int first = n / pow_result;
  int second = n % pow_result;
  return std::make_pair(first, second);
}

/**
@brief: making S_n is something like this:::

make_s(2023) =>
  S_n = {2023, 202+3, 20+23, 2+023, 20+2+3, 2+02+3, 2+0+23, 2+0+2+3}
*/
static Set make_s(int n) {
  int digits = digits_of(n);
  Set ret = {n}; // itself when `number_of_plus` == 0

  for (int i = 1; i < digits; ++i) {
    // split this number from i-th digit
    auto splitted = split_int(n, i);
    Set tmps = make_s(splitted.first);
    for (int from_first : tmps) {
      ret.insert(from_first + splitted.second);
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
