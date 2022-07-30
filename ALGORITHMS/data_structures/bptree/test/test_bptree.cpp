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

TEST_F(BPTreeFixture, InsertAndQuery)
{
  // const auto record = std::make_shared<Record>(1, 1, "male", 100);
  // const auto key = record->mId;
  // mTree.insert(record, key);
}
