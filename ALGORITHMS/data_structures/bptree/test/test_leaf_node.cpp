#include <gtest/gtest.h>
#include <bptree.hpp>
#include <memory>

class LeafNodeFixture : public ::testing::Test
{
protected:
  using Key = int;
  static constexpr int M = 5;
  auto SetUp() -> void override
  {
    leafNode = bptree::LeafNode<Key, Record, M>{};
  }
  auto TearDown() -> void override
  {
  }

  struct Record
  {
    int id;
    int grade;
    char gender[7];
    int score;
  };
  bptree::LeafNode<Key, Record, M> leafNode;
};

TEST_F(LeafNodeFixture, KeySize)
{
  auto const records =
      {
          Record{20, 1, "male", 300},
          Record{10, 1, "male", 301},
          Record{30, 2, "female", 250},
          Record{40, 2, "female", 350},
          Record{50, 3, "male", 150},
      };
  size_t cnt = 0;
  for (auto const &r : records)
  {
    leafNode.insert(std::make_shared<Record>(r), r.id);
    EXPECT_EQ(leafNode.keySize(), ++cnt);
  }
}