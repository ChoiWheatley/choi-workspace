#include <bptree.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <set>
#include <string>
#include <vector>

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
  const auto extra = keys[0];
  // EXPECT_THROW({ nonLeafNode.insert(extra); }, bptree::node_overflow);
}

TEST_F(NonLeafKeyTest, KeySizeWhenRemove)
{
  for (const auto &k : keys)
  {
    nonLeafNode.insert(k);
  }
  ASSERT_TRUE(nonLeafNode.full());
  auto cnt = M;
  for (const auto &k : keys)
  {
    nonLeafNode.remove(k);
    EXPECT_EQ(nonLeafNode.keyCount(), --cnt);
  }
  EXPECT_TRUE(nonLeafNode.empty());
  const auto extra = keys[0];
  EXPECT_THROW({ nonLeafNode.remove(extra); }, bptree::node_underflow);
}

class NonLeafChildTest : public ::testing::Test
{
protected:
  using Key = int;
  struct Record
  {
    int id;
    const char *name;
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
        nonLeafChildNodes{},
        leafChildNodes{},
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
        }
  {
    for (size_t i = 0; i < 2; ++i)
    {
      nonLeafChildNodes.push_back(std::make_shared<NonLeafNode_>(factory.childContainer()));
    }
    for (size_t i = 0; i < 5; ++i)
    {
      leafChildNodes.push_back(std::make_shared<LeafNode_>());
    }
  };
  auto SetUp() -> void override
  /*
  [70, , ]
  ├─[30, 50, ]
  │ ├─[10, 20, ]
  │ ├─[30, 40, ]
  │ └─[50, 60, ]
  └─[90, , ]
    ├─[70, 80, ]
    └─[90, 100, ]
  */
  {
    root.insert(70);
    nonLeafChildNodes[0]->insert(30);
    nonLeafChildNodes[0]->insert(50);
    nonLeafChildNodes[1]->insert(90);
    for (const auto &firstLevel : nonLeafChildNodes)
    {
      // TODO: Parent setter가 필요함.
      // firstLevel->parent(root);
    }
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
    leafChildNodes[0]->attach(leafChildNodes[1]);
    leafChildNodes[1]->attach(leafChildNodes[2]);
    leafChildNodes[2]->attach(leafChildNodes[3]);
    leafChildNodes[3]->attach(leafChildNodes[4]);
  }
  auto TearDown() -> void override {}

  BPFactory_ factory;
  NonLeafNode_ root;
  std::vector<NonLeafNodePtr> nonLeafChildNodes;
  std::vector<LeafNodePtr> leafChildNodes;
  std::vector<Record> records;
};

TEST_F(NonLeafChildTest, AttachSingleChild)
{
  auto rootCnt = size_t{0};
  EXPECT_EQ(root.childCount(), rootCnt);
  root.attach(nonLeafChildNodes[0]);
  EXPECT_EQ(root.childCount(), ++rootCnt);
}

TEST_F(NonLeafChildTest, AttachChild)
{
  // nonLeafChildNodes
  auto rootCnt = size_t{0};
  root.attach(nonLeafChildNodes[0]);
  EXPECT_EQ(root.childCount(), ++rootCnt);
  root.attach(nonLeafChildNodes[1]);
  EXPECT_EQ(root.childCount(), ++rootCnt);
  // leafChildNodes
  {
    auto firstLevelCnt = size_t{0};
    const auto firstLevel = nonLeafChildNodes[0];
    firstLevel->attach(leafChildNodes[0]);
    EXPECT_EQ(firstLevel->childCount(), ++firstLevelCnt);
    firstLevel->attach(leafChildNodes[1]);
    EXPECT_EQ(firstLevel->childCount(), ++firstLevelCnt);
    firstLevel->attach(leafChildNodes[2]);
    EXPECT_EQ(firstLevel->childCount(), ++firstLevelCnt);
  }
  {
    auto firstLevelCnt = size_t{0};
    const auto firstLevel = nonLeafChildNodes[1];
    firstLevel->attach(leafChildNodes[3]);
    EXPECT_EQ(firstLevel->childCount(), ++firstLevelCnt);
    firstLevel->attach(leafChildNodes[4]);
    EXPECT_EQ(firstLevel->childCount(), ++firstLevelCnt);
  }
  // testing for weird ranged child
  // attach [69,70,71] into root([70, , ]) will throw bptree::child_out_of_range
  {
    const auto weirdChild = std::make_shared<NonLeafNode_>(factory.childContainer());
    weirdChild->insert(Key{69});
    weirdChild->insert(Key{70});
    weirdChild->insert(Key{71});
    EXPECT_THROW({ root.attach(weirdChild); }, bptree::child_out_of_range);
  }
  // Did `Do-or-Nothing` principle satisfy?
  EXPECT_EQ(root.childCount(), rootCnt);
}

TEST_F(NonLeafChildTest, GetChildNodes)
{
  // inversed-insert child nodes
  root.attach(nonLeafChildNodes[1]);
  root.attach(nonLeafChildNodes[0]);
  const auto childNodesOfRoot = root.childNodes();
  for (size_t i = 0; i < root.childCount(); ++i)
  {
    EXPECT_TRUE(childNodesOfRoot.at(i)->keys() == nonLeafChildNodes.at(i)->keys());
  }
}

TEST_F(NonLeafChildTest, DetachChild)
{
  {
    root.attach(nonLeafChildNodes[0]);
    root.attach(nonLeafChildNodes[1]);
    EXPECT_EQ(root.childCount(), 2);
    EXPECT_EQ(nonLeafChildNodes[0].use_count(), 2);
    EXPECT_EQ(nonLeafChildNodes[1].use_count(), 2);
    // d0 would be a node [30, 50, ]
    const auto d0 = root.detachChildBy(0);
    EXPECT_EQ(d0->keys().at(0), 30);
    EXPECT_EQ(root.childCount(), 1);
    EXPECT_EQ(nonLeafChildNodes[0].use_count(), 1);
    // d1 would be a node [90, , ]
    const auto d1 = root.detachChildBy(1);
    EXPECT_EQ(d1->keys().at(0), 90);
    EXPECT_EQ(root.childCount(), 0);
    EXPECT_EQ(nonLeafChildNodes[1].use_count(), 1);
  }
  root.attach(nonLeafChildNodes[0]);
  root.attach(nonLeafChildNodes[1]);
  {
    const auto firstLevel = nonLeafChildNodes[0];
    firstLevel->attach(leafChildNodes[0]);
    firstLevel->attach(leafChildNodes[1]);
    firstLevel->attach(leafChildNodes[2]);
    EXPECT_EQ(firstLevel->childCount(), 3);
    EXPECT_EQ(leafChildNodes[0].use_count(), 2);
    EXPECT_EQ(leafChildNodes[1].use_count(), 3); // sibling count
    EXPECT_EQ(leafChildNodes[2].use_count(), 3); // sibling count
    // d0 = [10, 20, ]
    const auto d0 = firstLevel->detachChildBy(0);
    EXPECT_EQ(d0->keys().at(0), 10);
    EXPECT_EQ(firstLevel->childCount(), 2);
    EXPECT_EQ(leafChildNodes.at(0).use_count(), 1);
    // d1 = [30, 40, ]
    const auto d1 = firstLevel->detachChildBy(0);
    EXPECT_EQ(d1->keys().at(0), 30);
    EXPECT_EQ(firstLevel->childCount(), 1);
    EXPECT_EQ(leafChildNodes[1].use_count(), 2);
    // d2 = [50, 60, ]
    const auto d2 = firstLevel->detachChildBy(0);
    EXPECT_EQ(d2->keys().at(0), 50);
    EXPECT_EQ(firstLevel->childCount(), 0);
    EXPECT_EQ(leafChildNodes[2].use_count(), 2);
  }
  {
    const auto firstLevel = nonLeafChildNodes[1];
    firstLevel->attach(leafChildNodes[3]);
    firstLevel->attach(leafChildNodes[4]);
    EXPECT_EQ(firstLevel->childCount(), 2);
    EXPECT_EQ(leafChildNodes[3].use_count(), 3); // sibling count
    EXPECT_EQ(leafChildNodes[4].use_count(), 3); // sibling count
    // d0 = [70, 80, ]
    const auto d0 = firstLevel->detachChildBy(0);
    EXPECT_EQ(d0->keys().at(0), 70);
    EXPECT_EQ(firstLevel->childCount(), 1);
    EXPECT_EQ(leafChildNodes[3].use_count(), 2);
    // d1 = [90, 100, ]
    const auto d1 = firstLevel->detachChildBy(0);
    EXPECT_EQ(d1->keys().at(0), 90);
    EXPECT_EQ(firstLevel->childCount(), 0);
    EXPECT_EQ(leafChildNodes[4].use_count(), 2);
  }
}

TEST_F(NonLeafChildTest, ChildValidation)
{
  root.attach(nonLeafChildNodes[0]);
  root.attach(nonLeafChildNodes[1]);
  EXPECT_NO_THROW({ root.validateChildNodes(); });
  nonLeafChildNodes[0]->attach(leafChildNodes[0]);
  nonLeafChildNodes[0]->attach(leafChildNodes[1]);
  nonLeafChildNodes[0]->attach(leafChildNodes[2]);
  EXPECT_NO_THROW({ nonLeafChildNodes[0]->validateChildNodes(); });
  nonLeafChildNodes[1]->attach(leafChildNodes[3]);
  nonLeafChildNodes[1]->attach(leafChildNodes[4]);
  EXPECT_NO_THROW({ nonLeafChildNodes[1]->validateChildNodes(); });
}
