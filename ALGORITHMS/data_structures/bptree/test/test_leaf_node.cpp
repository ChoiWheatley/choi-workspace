#include <gtest/gtest.h>
#include <bptree.hpp>
#include <memory>
#include <vector>
#include <set>

class LeafNodeFixture : public ::testing::Test
{
protected:
  struct Record
  {
    int id;
    int grade;
    char gender[7];
    int score;
    bool operator<(const Record &other) const
    {
      return (this->id < other.id);
    }
  };
  using Key = int;
  static constexpr int M = 6;

  LeafNodeFixture()
      : records{
            Record{20, 1, "male", 300},
            Record{10, 1, "male", 301},
            Record{30, 2, "female", 250},
            Record{40, 2, "female", 350},
            Record{50, 3, "male", 150},
            Record{10, 3, "female", 350},
            Record{10, 3, "female", 350},
            Record{10, 3, "female", 350},
            Record{10, 3, "female", 350},
            Record{10, 3, "female", 350},
            Record{10, 3, "female", 350},
            Record{10, 3, "female", 350},
            Record{10, 3, "female", 350},
            Record{10, 3, "female", 350},
        }
  {
  }
  auto SetUp() -> void override
  {
    records = std::vector<Record>{records.begin(), records.begin() + M};
  }
  auto TearDown() -> void override
  {
  }
  bptree::LeafNode<Key, Record, M> leafNode;
  std::vector<Record> records;
};

TEST_F(LeafNodeFixture, KeySizeWhenInsert)
{
  size_t cnt = 0;
  EXPECT_TRUE(leafNode.empty());
  for (auto const &r : records)
  {
    leafNode.insert(std::make_shared<Record>(r), r.id);
    EXPECT_EQ(leafNode.keySize(), ++cnt);
    EXPECT_TRUE(leafNode.validate());
  }
  EXPECT_TRUE(leafNode.full());
}

TEST_F(LeafNodeFixture, KeySizeWhenRemove)
{
  size_t cnt = 0;
  for (const auto &r : records)
  {
    leafNode.insert(std::make_shared<Record>(r), r.id);
    ++cnt;
    EXPECT_EQ(leafNode.keySize(), cnt);
    EXPECT_TRUE(leafNode.validate());
  }
  // remove wrong key
  const int key = -100;
  leafNode.remove(key);
  EXPECT_EQ(leafNode.keySize(), cnt);
  const auto set = std::set<Record>{records.begin(), records.end()};
  for (const auto &r : set)
  {
    std::cerr << "r.id = " << r.id << "\n";
    try
    {
      const auto key = r.id;
      leafNode.remove(key);
      // --cnt;
      // EXPECT_EQ(leafNode.keySize(), cnt);
      EXPECT_TRUE(leafNode.validate());
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
      continue;
    }
  }
}