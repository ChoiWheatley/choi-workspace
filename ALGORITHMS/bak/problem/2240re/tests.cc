#include "solution.hpp"
#include <gtest/gtest.h>

TEST(Sol, 1) {
  vector<int> t = {1, 0, 0, 1, 1, 0, 0};
  int w = 2;
  int answer = 6;
  int submit = solution(t, w);
  ASSERT_EQ(answer, submit);
}

TEST(Sol, 2) {
  vector<int> t = {0, 1, 0, 1, 0, 1};
  int w = 5;
  int answer = 6;
  int submit = solution(t, w);
  ASSERT_EQ(answer, submit);
}

TEST(Sol, 3) {
  vector<int> t = {1, 0};
  int w = 1;
  int answer = 1;
  int submit = solution(t, w);
  ASSERT_EQ(answer, submit);
}

TEST(Sol, 4) {
  vector<int> t = {0};
  int w = 1;
  int answer = 1;
  int submit = solution(t, w);
  ASSERT_EQ(answer, submit);
}

TEST(Sol, 5) {
  vector<int> t = {1, 0, 0};
  int w = 1;
  int answer = 2;
  int submit = solution(t, w);
  ASSERT_EQ(answer, submit);
}