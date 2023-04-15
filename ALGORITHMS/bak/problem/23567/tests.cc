#include "solution.hpp"
#include <gtest/gtest.h>
#include <random.hpp>

using namespace std;

TEST(Sol, 1) {
  auto ls = Vec{1, 2, 3, 1, 1, 4, 2, 4, 3, 3};
  size_t k = 4;
  auto answer = 5;
  ASSERT_EQ(answer, solution(std::move(ls), k));
}
TEST(Sol, 2) {
  auto ls = Vec{
      1, 1, 2, 2, 3, 3,
  };
  size_t k = 3;
  auto answer = 0;
  ASSERT_EQ(answer, solution(std::move(ls), k));
}
TEST(Timeout, 1) {
  constexpr size_t N = 1000;

  Random<int> rand;

  auto ls = Vec(N);
  for (size_t k = 50; k < 51; ++k) {
    for (auto &e : ls) {
      e = (rand.next() % (k - 1)) + 1;
    }
    solution(std::move(ls), k);
  }
}