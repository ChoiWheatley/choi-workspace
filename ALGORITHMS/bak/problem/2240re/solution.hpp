#ifndef SOLUTION
#define SOLUTION

#include <cstring>
#include <vector>
#define cr const &

using namespace std;

constexpr int MAX_TIME = 1001;
constexpr int MAX_JUMP = 31;
constexpr int MAX_TREE = 2;

int dp[MAX_TIME][MAX_JUMP];

/**
@breif:
t초에 자두가 n번 점프했을 때 자두가 받을 수 있는 자두열매 개수의 최댓값
*/
int sol_recur(vector<int> cr schedule, int jump_max, int time_max,
              int jump_count, int time_passed) {
  if (time_passed >= time_max) {
    return 0;
  }

  auto &ref = dp[time_passed][jump_count];
  if (ref != -1) {
    return ref;
  }

  auto pos = jump_count % 2;
  auto no_jump =
      sol_recur(schedule, jump_max, time_max, jump_count, time_passed + 1) +
      (schedule[time_passed] == pos ? 1 : 0);

  if (jump_count < jump_max) {
    auto yes_jump = sol_recur(schedule, jump_max, time_max, jump_count + 1,
                              time_passed + 1) +
                    (schedule[time_passed] != pos ? 1 : 0);

    return ref = std::max(no_jump, yes_jump);
  }

  return ref = no_jump;
}

int solution(vector<int> cr schedule, int jump_max) {
  memset(dp, -1, sizeof(dp));
  return sol_recur(schedule, jump_max, int(schedule.size()), 0, 0);
}

#endif