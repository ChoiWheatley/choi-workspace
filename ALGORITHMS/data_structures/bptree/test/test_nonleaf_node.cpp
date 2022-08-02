#include <gtest/gtest.h>
#include <bptree.hpp>
#include <memory>
#include <vector>
#include <set>

class NonLeafKeyTest : public ::testing::Test
{
protected:
  struct Record;
  using Key = int;
  static constexpr size_t M = 5;
  using BPFactory_ = typename bptree::BPFactory<Key, Record, M>;
  using NonLeafNode_ = typename bptree::NonLeafNode<Key, Record, M>;

  NonLeafKeyTest()
      : factory{BPFactory_{}},
        nonLeafNode{factory.childContainer()},
        keys{
            10,
            20,
            40,
            80,
            160,
            15,
            30,
            60,
            120,
            12,
            24,
            48,
            96,
        } {};

  auto SetUp() -> void override
  {
    keys = std::vector<Key>{keys.begin(), keys.begin() + M};
  }
  auto TearDown() -> void override
  {
  }

  BPFactory_ factory;
  NonLeafNode_ nonLeafNode;
  std::vector<Key> keys;
};

TEST_F(NonLeafKeyTest, KeySizeWhenInsert)
{
  EXPECT_TRUE(nonLeafNode.empty());
  size_t cnt = 0;
  for (const auto &k : keys)
  {
    nonLeafNode.insert(k);
    EXPECT_EQ(nonLeafNode.keyCount(), ++cnt);
  }
  EXPECT_TRUE(nonLeafNode.full());
  const auto extra = Key{1};
  EXPECT_THROW({ nonLeafNode.insert(extra); }, bptree::node_overflow);
}

TEST_F(NonLeafKeyTest, KeySizeWhenRemove)
{
  for (const auto &k : keys)
  {
    nonLeafNode.insert(k);
  }
  // TODO: deletion start
}

class NonLeafChildTest : public ::testing::Test
{
protected:
  using Key = int;
  struct Record
  {
    int id;
    std::string name;
  };
  static constexpr int M = 3;
  using BPFactory_ = typename bptree::BPFactory<Key, Record, M>;
  using NonLeafNode_ = typename bptree::NonLeafNode<Key, Record, M>;
  using NonLeafNodePtr = std::shared_ptr<NonLeafNode_>;
  using LeafNode_ = typename bptree::LeafNode<Key, Record, M>;
  using LeafNodePtr = std::shared_ptr<LeafNode_>;

  NonLeafChildTest()
      : factory{},
        root{factory.childContainer()},
        nonLeafChildNodes{2, factory.nonLeafNode()},
        leafChildNodes{5},
        records{
            Record{10, "a"},
            Record{20, "b"},
            Record{30, "c"},
            Record{40, "d"},
            Record{50, "e"},
            Record{60, "f"},
            Record{70, "g"},
            Record{80, "h"},
            Record{90, "i"},
            Record{100, "j"},
        } {};
  auto SetUp() -> void override
  {
    root.insert(70);
    nonLeafChildNodes[0]->insert(30);
    nonLeafChildNodes[0]->insert(50);
    nonLeafChildNodes[1]->insert(90);
    leafChildNodes[0]->insert(std::make_shared<Record>(records[0]), records[0].id);
    leafChildNodes[0]->insert(std::make_shared<Record>(records[1]), records[1].id);
    leafChildNodes[1]->insert(std::make_shared<Record>(records[2]), records[2].id);
    leafChildNodes[1]->insert(std::make_shared<Record>(records[3]), records[3].id);
    leafChildNodes[2]->insert(std::make_shared<Record>(records[4]), records[4].id);
    leafChildNodes[2]->insert(std::make_shared<Record>(records[5]), records[5].id);
    leafChildNodes[3]->insert(std::make_shared<Record>(records[6]), records[6].id);
    leafChildNodes[3]->insert(std::make_shared<Record>(records[7]), records[7].id);
    leafChildNodes[4]->insert(std::make_shared<Record>(records[8]), records[8].id);
    leafChildNodes[4]->insert(std::make_shared<Record>(records[9]), records[9].id);
  }
  auto TearDown() -> void override {}

  BPFactory_ factory;
  NonLeafNode_ root;
  std::vector<NonLeafNodePtr> nonLeafChildNodes;
  std::vector<LeafNodePtr> leafChildNodes;
  std::vector<Record> records;
};

TEST_F(NonLeafChildTest, AttachChild)
{
}

TEST_F(NonLeafChildTest, DetachChild)
{
}

TEST_F(NonLeafChildTest, ChildValidation)
{
}