#include "solution.hpp"
#include <gtest/gtest.h>
#include <numeric>
#include <random.hpp>
#include <vector>

using namespace std;

constexpr size_t MAX_N = 100'000;
constexpr i64 MAX_ELEM = 10'000;
constexpr i64 MAX_S = 100'000'000;

TEST(PartialSum, 1) {
  auto seq = Vec{5, 1, 3, 5, 10, 7, 4, 9, 2, 8};
  std::partial_sum(seq.begin(), seq.end(), seq.begin());
  ASSERT_EQ(Vec({5, 6, 9, 14, 24, 31, 35, 44, 46, 54}), seq);
}

TEST(Sol, 1) {
  auto seq = Vec{5, 1, 3, 5, 10, 7, 4, 9, 2, 8};
  std::partial_sum(seq.begin(), seq.end(), seq.begin());
  size_t answer = 2;
  i64 S = 15;
  ASSERT_EQ(answer, solution(std::move(seq), S));
}

TEST(Timeout, 1) {
  Vec seq;
  Random<i64> rnd;
  for (size_t i = 0; i < MAX_N; ++i) {
    seq.push_back((rnd.next() % (MAX_ELEM - 1)) + 1);
  }
  std::partial_sum(seq.begin(), seq.end(), seq.begin());
  solution(std::move(seq), MAX_S);
}

TEST(Timeout, 2) {
  Vec seq(MAX_N);
  for (auto &e : seq) {
    e = 1;
  }
  std::partial_sum(seq.begin(), seq.end(), seq.begin());
  ASSERT_EQ(0, solution(std::move(seq), MAX_S));
}

TEST(CornerCases, 1) {
  i64 s = 10;
  ASSERT_EQ(1, solution(Vec{10}, s));
}

TEST(CornerCases, 2) {
  auto seq = Vec{1, 10, 1, 1, 1};
  std::partial_sum(seq.begin(), seq.end(), seq.begin());
  i64 s = 10;
  ASSERT_EQ(1, solution(std::move(seq), s));
}

TEST(CornerCases, 3) {
  auto seq = Vec{1, 1, 1, 1, 1, 1, 1, 1, 1, 10};
  std::partial_sum(seq.begin(), seq.end(), seq.begin());
  i64 s = 10;
  ASSERT_EQ(1, solution(std::move(seq), s));
}
TEST(CornerCases, 4) {
  auto seq = Vec{1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  std::partial_sum(seq.begin(), seq.end(), seq.begin());
  i64 s = 10;
  ASSERT_EQ(10, solution(std::move(seq), s));
}
TEST(CornerCases, 5) {
  auto seq = Vec{1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  std::partial_sum(seq.begin(), seq.end(), seq.begin());
  i64 s = 0;
  ASSERT_EQ(1, solution(std::move(seq), s));
}
TEST(CornerCases, 6) {
  auto seq = Vec{5, 1, 3, 5, 10, 7, 4, 9, 2, 8};
  std::partial_sum(seq.begin(), seq.end(), seq.begin());
  i64 s = 100;
  ASSERT_EQ(0, solution(std::move(seq), s));
}
TEST(CornerCases, 7) {
  auto seq = Vec{1, 1, 1, 8, 10};
  std::partial_sum(seq.begin(), seq.end(), seq.begin());
  i64 s = 10;
  ASSERT_EQ(1, solution(std::move(seq), s));
}
TEST(CornerCases, 8) {
  auto seq = Vec{10, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  std::partial_sum(seq.begin(), seq.end(), seq.begin());
  i64 s = 10;
  ASSERT_EQ(1, solution(std::move(seq), s));
}
TEST(CornerCases, 9) {
  auto seq = Vec{2, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  std::partial_sum(seq.begin(), seq.end(), seq.begin());
  i64 s = 2;
  ASSERT_EQ(1, solution(std::move(seq), s));
}
TEST(CornerCases, 10) {
  auto seq = Vec{3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
  std::partial_sum(seq.begin(), seq.end(), seq.begin());
  i64 s = 10;
  ASSERT_EQ(4, solution(std::move(seq), s));
}
TEST(CornerCases, 11) {
  auto seq = Vec{1, 2, 2, 3};
  std::partial_sum(seq.begin(), seq.end(), seq.begin());
  i64 s = 5;
  ASSERT_EQ(2, solution(std::move(seq), s));
}