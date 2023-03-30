#ifndef SOLUTION
#define SOLUTION

#include <array>
#include <cstddef>
#include <iostream>
using std::array;

constexpr size_t MAX_N = 1024;
using Arr = array<array<int, MAX_N>, MAX_N>;

constexpr bool is_inside(int row, int col, int n, int m) {
  return 0 <= row && row < n && 0 <= col && col < m;
}

inline int get_or(Arr const &arr, int row, int col, int n, int m, int orthan) {
  if (is_inside(row, col, n, m)) {
    return arr[row][col];
  }
  return orthan;
}

/**
@breif: arr 이차원 누적배열의 row와 col에 value를 추가한다.

arr[i][j] = arr[i-1][j] + arr[i][j-1] - arr[i-1][j-1]
*/
inline void add_to(Arr &arr, int row, int col, int n, int m, int value) {
  auto &ref = arr[row][col];
  ref = value;
  ref += get_or(arr, row - 1, col, n, m, 0);
  ref += get_or(arr, row, col - 1, n, m, 0);
  ref -= get_or(arr, row - 1, col - 1, n, m, 0);
}

/**
@breif: arr 이차원 누적배열로부터 기존 배열의 구간합 from: (a1,b1), to:
(a2,b2)를 구한다. (inclusive)

= arr[a2][b2] - arr[a2][b1-1] - arr[a1-1][b2] + arr[a1-1][b1-1]
*/
inline int sum_between(Arr const &arr, int a1, int b1, int a2, int b2, int n,
                       int m) {
  if (a1 > a2) {
    std::swap(a1, a2);
  }
  if (b1 > b2) {
    std::swap(b1, b2);
  }
  auto result = arr[a2][b2];
  result -= get_or(arr, a2, b1 - 1, n, m, 0);
  result -= get_or(arr, a1 - 1, b2, n, m, 0);
  result += get_or(arr, a1 - 1, b1 - 1, n, m, 0);
  return result;
}

#endif