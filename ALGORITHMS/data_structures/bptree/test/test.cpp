#include "helpers.hpp"
#include "key_record.hpp"
#include "real_factory.hpp"
#include <bptree.hpp>
#include <gtest/gtest.h>
#include <tuple>

TEST(Init, ForBetterCompilation)
{
  constexpr size_t M = 3;
  const vector<R> records{
      R{1, "name", R::Freshman},
      R{2, "name1", R::Freshman},
      R{3, "name2", R::Freshman},
      R{4, "name3", R::Freshman},
      R{5, "name4", R::Freshman},
      R{6, "name5", R::Freshman},
  };
  // auto record = RecordImpl<Key>{1, "name", R::Male, 100, R::Freshman};

  const auto realFactory = RealFactory<Key>{};
  const auto bpt = realFactory.makeTree(M);

  for (const auto &r : records)
  {
    bpt->Add(std::make_unique<R>(r));
  }

  bpt->Find(Key{1});

  bpt->Delete(Key{1});
}

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
  const vector<Key> sampleKeys2 = {10, 20, 15, 30, 12, 24, 36, 11, 22, 33, 44};
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