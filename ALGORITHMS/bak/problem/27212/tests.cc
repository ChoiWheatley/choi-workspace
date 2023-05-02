#include "solution.hpp"
#include <gtest/gtest.h>
#include <random.hpp>
#include <vector>

using std::vector;

TEST(Sol, 1) {
  vector<vector<i64>> w = {{1, 1, 1}, {1, 100, 1}, {1, 1, 1}};
  vector<usize> a = {0, 0, 0, 0, 0, 1};
  vector<usize> b = {
      1, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  };
  ASSERT_EQ(100, solution(w, a, b));
}

TEST(Edge, 1) {
  Random<usize> r;

  vector<vector<i64>> w;
  vector<usize> a, b;

  constexpr usize MAX_N = 1000;
  constexpr usize MAX_M = 1000;

  for (usize i = 0; i < C; ++i) {
    vector<i64> line;
    for (usize j = 0; j < C; ++j) {
      line.push_back(r.next() % 1000000000);
    }
    w.push_back(line);
  }

  for (usize i = 0; i < MAX_N; ++i) {
    a.push_back(r.next() % C);
  }

  for (usize i = 0; i < MAX_M; ++i) {
    b.push_back(r.next() % C);
  }

  solution(w, a, b);
}