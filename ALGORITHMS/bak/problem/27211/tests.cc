#include "solution.hpp"
#include <gtest/gtest.h>
#include <initializer_list>

TEST(Univ, get_index) {
  Universe u{BitSet(), 3, 4};
  ASSERT_EQ(3, u.get_index(0, -1));
  ASSERT_EQ(8, u.get_index(-1, 0));
  ASSERT_EQ(11, u.get_index(-1, -1));
}

static UniverseBuilder easy_ub(std::vector<std::vector<int>> cr map) {
  UniverseBuilder ub(Idx(map.size()), Idx(map[0].size()));
  for (int i = 0; i < int(map.size()); ++i) {
    for (int j = 0; j < int(map[0].size()); ++j) {
      if (map[i][j] == 0) {
        ub.add_empty(i, j);
      }
    }
  }
  return ub;
}

TEST(Sol, 1) {
  auto ub = UniverseBuilder(5, 6);
  ub.add_empty(1, 1);
  ub.add_empty(1, 2);
  ub.add_empty(1, 3);

  ub.add_empty(2, 4);
  ub.add_empty(2, 5);
  ub.add_empty(3, 4);
  ub.add_empty(3, 5);

  ASSERT_EQ(2, solution(ub));
}

TEST(Sol, 2) {
  const vector<vector<int>> map = {
      {0, 0, 1, 1, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 0, 1, 0},
      {1, 1, 1, 1, 1, 1, 1, 1}, {0, 1, 1, 1, 1, 1, 0, 0},
      {1, 1, 0, 0, 0, 1, 0, 0}, {0, 1, 0, 0, 0, 1, 0, 1},
      {0, 0, 1, 1, 1, 1, 0, 0},
  };
  auto ub = easy_ub(map);
  ASSERT_EQ(2, solution(ub));
}