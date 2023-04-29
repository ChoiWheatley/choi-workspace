#include "solution.hpp"
#include <gtest/gtest.h>
#include <utility>

using namespace std;

TEST(Sol, 1) {
  deque<Card> cards = {1, 2, 5, 2};
  auto answer = make_pair(Score(6), Score(4));
  ASSERT_EQ(answer, solution(move(cards)));
}

TEST(Sol, 2) {
  deque<Card> cards = {4, 3, 1, 2};
  auto answer = make_pair(Score(6), Score(4));
  ASSERT_EQ(answer, solution(move(cards)));
}

TEST(Sol, 3) {
  deque<Card> cards = {1, 2, 3, 5, 2};
  auto answer = make_pair(Score(6), Score(7));
  ASSERT_EQ(answer, solution(move(cards)));
}

TEST(Sol, 4) {
  deque<Card> cards = {1, 1, 1, 1, 2, 2, 2, 2, 2};
  auto answer = make_pair(Score(8), Score(6));
  ASSERT_EQ(answer, solution(move(cards)));
}