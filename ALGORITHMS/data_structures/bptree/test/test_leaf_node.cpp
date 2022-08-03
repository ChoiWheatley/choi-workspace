#include <bptree.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <set>
#include <vector>

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
  static constexpr int M = 11;

  LeafNodeFixture()
      : records{
            Record{2, 1, "male", 300},
            Record{4, 1, "male", 301},
            Record{8, 2, "female", 250},
            Record{16, 2, "female", 350},
            Record{3, 3, "male", 150},
            Record{6, 3, "female", 350},
            Record{12, 3, "female", 350},
            Record{4, 3, "female", 650},
            Record{8, 3, "female", 350},
            Record{16, 3, "female", 700},
            Record{32, 3, "female", 350},
            Record{5, 3, "female", 350},
            Record{10, 3, "female", 350},
            Record{20, 3, "female", 350},
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
    EXPECT_EQ(leafNode.keyCount(), ++cnt);
    EXPECT_TRUE(leafNode.validate());
  }
  EXPECT_TRUE(leafNode.full());
  const auto r = Record{100, 5, "male", 1};
  EXPECT_THROW({ leafNode.insert(std::make_shared<Record>(r), r.id); }, bptree::node_overflow);
}

TEST_F(LeafNodeFixture, KeySizeWhenRemove)
{
  size_t cnt = 0;
  for (const auto &r : records)
  {
    leafNode.insert(std::make_shared<Record>(r), r.id);
    ++cnt;
    EXPECT_EQ(leafNode.keyCount(), cnt);
    EXPECT_TRUE(leafNode.validate());
  }
  // remove wrong key
  const int key = -100;
  leafNode.remove(key);
  EXPECT_EQ(leafNode.keyCount(), cnt);
  const auto set = std::set<Record>{records.begin(), records.end()};
  for (const auto &r : set)
  {
    try
    {
      const auto key = r.id;
      leafNode.remove(key);
      EXPECT_TRUE(leafNode.validate());
      for (const auto e : leafNode.keys())
      {
        std::cerr << e << ", ";
      }
      std::cerr << "\n";
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
      continue;
    }
  }
  EXPECT_THROW({ leafNode.remove(1); }, bptree::node_underflow);
}