#include "solution.hpp"
#include <gtest/gtest.h>
#include <vector>

TEST(timeout, 1) {
  vector<i64> ls(N);
  ASSERT_EQ(2000, solution(std::move(ls)));
}

TEST(Sol, 1) {
  auto ls = vector<i64>{-5, -2, -3};
  size_t answer = 1;
  ASSERT_EQ(answer, solution(std::move(ls)));
}
TEST(Sol, 2) {
  auto ls = vector<i64>{0, 0, 0};
  size_t answer = 3;
  ASSERT_EQ(answer, solution(std::move(ls)));
}
TEST(Sol, 3) {
  auto ls = vector<i64>{0, 0, 1};
  size_t answer = 0;
  ASSERT_EQ(answer, solution(std::move(ls)));
}
TEST(Sol, 4) {
  auto ls = vector<i64>{0, 0, 0, 3, 3, 3, 3};
  size_t answer = 7;
  ASSERT_EQ(answer, solution(std::move(ls)));
}
TEST(Sol, 5) {
  auto ls = vector<i64>{1, 2, 3, 4, 5, 5, 5, 5};
  size_t answer = 6;
  ASSERT_EQ(answer, solution(std::move(ls)));
}
TEST(Sol, 6) {
  auto ls = vector<i64>{0, 0, 3, 3, 3, 3};
  size_t answer = 4;
  ASSERT_EQ(answer, solution(std::move(ls)));
}
TEST(Sol, 7) {
  auto ls = vector<i64>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  size_t answer = 8;
  ASSERT_EQ(answer, solution(std::move(ls)));
}