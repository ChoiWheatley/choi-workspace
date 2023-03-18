#ifndef SOLUTION
#define SOLUTION

#define cr const &

#include <cinttypes>
#include <vector>
using std::vector;

template <class Pred>
static int first_true(int begin, int end, Pred cr predicate) {
  int l = begin;
  int r = end;
  while (l < r) {
    int m = l + (r - l) / 2;
    if (predicate(m)) {
      // next range is [l, m)
      r = m;
    } else {
      // next range is [m + 1, r)
      l = m + 1;
    }
  }
  return l;
}

/**
@param:
- data: idx초에 떨어질 자두가 걸려있는 나무의 번호
- w: 다른 나무로 점프할 수 있는 횟수
@return:
  획득할 수 있는 자두의 최대 개수
*/
inline int solution(vector<int8_t> cr data, int w) {
  //
}

#endif