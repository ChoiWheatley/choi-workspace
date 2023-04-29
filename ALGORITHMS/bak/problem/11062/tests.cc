#include "solution.hpp"
#include <gtest/gtest.h>
#include <utility>

using namespace std;

TEST(Sol, 1) {
  vector<Score> cards = {1, 2, 5, 2};
  auto answer = 6;
  ASSERT_EQ(answer, solution(move(cards)));
}

TEST(Sol, 2) {
  vector<Score> cards = {4, 3, 1, 2};
  auto answer = 6;
  ASSERT_EQ(answer, solution(move(cards)));
}

TEST(Sol, 3) {
  vector<Score> cards = {1, 2, 3, 5, 2};
  auto answer = 6;
  ASSERT_EQ(answer, solution(move(cards)));
}

TEST(Sol, 4) {
  vector<Score> cards = {1, 1, 1, 1, 2, 2, 2, 2, 2};
  auto answer = 8;
  ASSERT_EQ(answer, solution(move(cards)));
}