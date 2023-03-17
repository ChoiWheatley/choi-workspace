#include <array>
#include <cstddef>
#include <iostream>
#include <tuple>
#include <unordered_set>

#define cr const &
constexpr int MAX_ID = 200;

using std::array;
using ArrArr = array<array<bool, MAX_ID + 1>, MAX_ID + 1>;

inline int solution(ArrArr cr connected, int n) {
  int cnt = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      for (int k = j + 1; k <= n; ++k) {
        if (!connected[i][j] && !connected[j][k] && !connected[i][k]) {
          cnt++;
        }
      }
    }
  }
  return cnt;
}
