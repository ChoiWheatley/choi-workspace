#include <bptree.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <string>

class BPTreeFixture : public ::testing::Test
{
protected:
  void SetUp() override
  {
    mTree = bptree::BPTree<Key, Record, M>{};
  }
  void TearDown() override
  {
  }

  struct Record
  {
    Record(int id, int grade, std::string gender, int score)
        : mId{id}, mGrade{grade}, mGender{gender}, mScore{score} {};
    int mId;
    int mGrade;
    std::string mGender;
    int mScore;
  };
  using Key = int;
  static constexpr int M = 4;

  bptree::BPTree<Key, Record, M> mTree;
};

// TEST_F(BPTreeFixture, InsertAndQuery)
// {
//   const auto record = std::make_shared<Record>(1, 1, "male", 100);
//   mTree.insert(keyrecord);
// }

TEST_F(BPTreeFixture, NodeSizeEqual)
{
  using AbstNode = typename bptree::AbstNode<Key, Record, M>;
  using LeafNode = typename bptree::LeafNode<Key, Record, M>;
  using NonLeafNode = typename bptree::NonLeafNode<Key, Record, M>;

  std::cout << "sizeof(AbstNode) = " << sizeof(AbstNode) << "\n";
  std::cout << "sizeof(LeafNode) = " << sizeof(LeafNode) << "\n";
  std::cout << "sizeof(NonLeafNode) = " << sizeof(NonLeafNode) << "\n";
  EXPECT_EQ(sizeof(LeafNode), sizeof(NonLeafNode));
}
