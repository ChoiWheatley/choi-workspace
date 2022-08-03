#include <bp_helpers.hpp>
#include <gtest/gtest.h>
#include <vector>

using bptree::maxIdxLessThan;
using bptree::minIdxLargerThan;

TEST(Comparism, MaxIndexLessThan)
{
  {
    const auto keys = std::vector<size_t>{10, 20, 30, 50, 60, 70};
    const auto key = size_t{40};
    EXPECT_EQ(maxIdxLessThan(key, keys, false), 2);
  }
  {
    const auto keys = std::vector<size_t>{10, 20, 30, 40, 40, 70};
    const auto key = size_t{40};
    EXPECT_EQ(maxIdxLessThan(key, keys, false), 4);
    EXPECT_EQ(maxIdxLessThan(key, keys, true), 2);
  }
}

TEST(Comparism, MinIndexLargerThan)
{
  {
    const auto keys = std::vector<size_t>{10, 20, 30, 50, 60, 70};
    const auto key = size_t{40};
    EXPECT_EQ(minIdxLargerThan(key, keys, false), 3);
  }
  {
    const auto keys = std::vector<size_t>{10, 20, 30, 40, 40, 70};
    const auto key = size_t{40};
    EXPECT_EQ(minIdxLargerThan(key, keys, false), 5);
    EXPECT_EQ(minIdxLargerThan(key, keys, true), 3);
  }
}