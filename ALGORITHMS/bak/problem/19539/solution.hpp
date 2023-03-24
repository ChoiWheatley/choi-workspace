#ifndef SOLUTION
#define SOLUTION

#include <vector>
using std::vector;

/**
@brief: 크기1짜리 블럭과 크기2짜리 블럭을 같은 수로 채워넣을 수 있는가?

# 전략:

1. 크기2짜리 블럭을 먼저 가득 채운 뒤 남는 공간을 크기1짜리 블럭으로 채운다.
2. 이때 크기1짜리 블럭들의 모임을 S1, 크기2짜리 블럭들의 모임을 S2로 정의한다.
3. 만약 size(S1) + 3n = size(S2)를 만족하는 정수 n의 해가 존재하면 True를,
아니면 False를 리턴한다.
*/
inline bool solution(vector<int> &ls) {
  int s1 = 0;
  int s2 = 0;
  for (auto &e : ls) {
    s2 += e / 2;
    e %= 2;
  }
  for (auto e : ls) {
    s1 += e;
  }
  if (s2 < s1) {
    return false;
  }
  // n ≡ (size(S2) - size(S1)) mod 3 인 n가 존재하는가?
  return (s2 - s1) % 3 == 0;
}

#endif