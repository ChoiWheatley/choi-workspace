#include "key_record.hpp"
#include "real_factory.hpp"
#include <bptree.hpp>
#include <gtest/gtest.h>
#include <helpers.hpp>

/// 냠냠
///
class Helpers : public ::testing::Test
{
protected:
  auto SetUp() -> void override
  {
  }
  auto TearDown() -> void override
  {
  }
  using KeyAnswerPair = std::pair<Key, size_t>;
  const vector<Key> sampleKeys1 = {10, 20, 30, 40, 50};
  const vector<Key> sampleKeys2 = {10, 20, 15, 30, 12, 24, 36, 11, 22, 33};
}; // class Helpers

TEST_F(Helpers, FindIndexBetween1)
{
  const vector<KeyAnswerPair> searchAnswerPairs =
      {{9, 0}, {10, 1}, {19, 1}, {20, 2}, {29, 2}, {30, 3}, {39, 3}, {40, 4}, {49, 4}, {50, 5}, {100, 5}};
  for (const auto &pair : searchAnswerPairs)
  {
    EXPECT_EQ(findIndexBetween(sampleKeys1, pair.first), pair.second);
  }
}

TEST_F(Helpers, Split)
{
  ASSERT_EQ(sampleKeys1.size(), 5);
  const auto &splitted = bptree::split(sampleKeys1);
  EXPECT_EQ(splitted.first.size(), 2);
  EXPECT_EQ(splitted.second.size(), 3);

  ASSERT_EQ(sampleKeys2.size(), 10);
  const auto &splitted2 = bptree::split(sampleKeys2);
  EXPECT_EQ(splitted2.first.size(), 5);
  EXPECT_EQ(splitted2.second.size(), 5);
}