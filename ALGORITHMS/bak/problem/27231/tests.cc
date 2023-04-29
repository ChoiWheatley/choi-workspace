#include "solution.hpp"
#include <gtest/gtest.h>
#include <random.hpp>
#include <string>

TEST(Parse, Int) {
  std::string s = "023";
  int answer = 23;
  ASSERT_EQ(answer, std::stoi(s));
}

constexpr int T = 1000;
constexpr int MAX_INT = (1 << 30) - 1;

TEST(Timeout, 1) {
  Random<int> r;
  for (int i = 0; i < T; ++i) {
    make_s(r.next() % MAX_INT);
  }
}

/**infinite loop detected!*/
TEST(Timeout, 2) { solution(101010101); }