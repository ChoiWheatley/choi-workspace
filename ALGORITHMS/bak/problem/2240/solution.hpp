#ifndef SOLUTION
#define SOLUTION

#include <algorithm>
#include <cstring>
#include <vector>
using std::vector;

#define cr const &

constexpr int MAX_JUMP = 31;
constexpr int MAX_TIME = 1001;
constexpr int MAX_POS = 2;

int dp[MAX_TIME][MAX_JUMP][MAX_POS];

int sol_recur(vector<int> cr schedule, int w, int now, int pos, int jump_cnt) {
  // base cond
  if (size_t(now) >= schedule.size()) {
    return 0;
  }

  auto &ref = dp[now][jump_cnt][pos];
  if (ref != -1) {
    return ref;
  }

  if (pos == schedule[now]) {
    // 나의 위치와 자두가 떨어질 위치가 같다.

    if (jump_cnt < w) {
      // 자리를 바꾸지 않고 자두를 챙기기 or 바꾸고 후일을 도모하기
      ref = std::max(sol_recur(schedule, w, now + 1, pos, jump_cnt) + 1,
                     sol_recur(schedule, w, now + 1, pos ^ 1, jump_cnt + 1));
    } else {
      // 가만히 있고 자두를 챙기기
      ref = std::max(ref, sol_recur(schedule, w, now + 1, pos, jump_cnt) + 1);
    }
  } else {
    // 나의 위치와 자두가 떨어질 위치가 다르다.
    if (jump_cnt < w) {
      // 자리를 바꾸지 않고 후일을 도모하기 or 바꾸고 자두를 챙기기
      ref =
          std::max(sol_recur(schedule, w, now + 1, pos, jump_cnt),
                   sol_recur(schedule, w, now + 1, pos ^ 1, jump_cnt + 1) + 1);
    } else {
      // 자리를 바꾸지 않고 후일을 도모한다.
      ref = std::max(ref, sol_recur(schedule, w, now + 1, pos, jump_cnt));
    }
  }
  return ref;
}

int solution(vector<int> cr schedule, int w) {
  memset(dp, -1, sizeof(dp));
  return sol_recur(schedule, w, 0, 0, 0);
}

#endif