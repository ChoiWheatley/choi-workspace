#include "key_record.hpp"
#include <bptree.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <stack>

using bptree::Has;
using std::make_shared;
using std::shared_ptr;
using std::stack;
using std::vector;
using _RecordImpl = RecordImpl<Key>;

template <class _K>
class AscenderExtension : public bptree::Ascender<_K>
{
  using _Ascender = bptree::Ascender<_K>;
  using _Node = bptree::Node<_K>;
  using _NodePtr = std::shared_ptr<_Node>;

public:
  auto parent() -> _NodePtr { return _Ascender::parent(); }
  auto descender() -> _NodePtr { return _Ascender::descender(); }
  auto ascender() const -> _NodePtr { return _Ascender::ascender(); }
  auto history() const -> const std::stack<_NodePtr>
  {
    return _Ascender::history();
  }
  auto cursor() const -> _NodePtr { return _Ascender::cursor(); }

  AscenderExtension(const _NodePtr ascender,
                    stack<_NodePtr> &&history,
                    _NodePtr cursor,
                    size_t maxKey) : _Ascender{ascender, std::move(history), cursor, maxKey} {}
}; // class AscenderExtension

class TestAscender1 : public ::testing::Test
{
public:
  using _Ascender = bptree::Ascender<Key>;
  using _Node = bptree::Node<Key>;
  using _NodePtr = std::shared_ptr<_Node>;
  using _Record = bptree::Record<Key>;
  using _RecordPtr = std::shared_ptr<_Record>;

protected:
  const size_t kMaxKey = 3;
  std::vector<RecordImpl<Key>> records = {
      {0, "name", Freshman},
      {1, "sarah", Sophomore},
      {2, "wheatley", Junior},
      {3, "tom", Senior},
      {4, "tobias", Freshman},
      {5, "linus", Sophomore},
      {6, "mackenzy", Junior},
  };
  _NodePtr rootNode = nullptr;
  std::vector<_NodePtr> children{3, nullptr};

  void
  SetUp()
  {
    /*
    [2,4,_]
    - [0,1,_]
    - [2,3,_]
    - [4,5,6]
    */
    using bptree::Has;
    rootNode = std::make_shared<_Node>(Has::ChildNodes);
    rootNode->keys = std::vector<Key>({2, 4});

    // init children
    for (auto &child : children)
    {
      child = std::make_shared<_Node>(Has::RecordPointers);
    }

    // connect records into each child
    children[0]->records =
        std::vector<_RecordPtr>{
            {std::make_shared<RecordImpl<Key>>(records[0]),
             std::make_shared<RecordImpl<Key>>(records[1])}};
    children[1]->records =
        std::vector<_RecordPtr>{
            {std::make_shared<RecordImpl<Key>>(records[2]),
             std::make_shared<RecordImpl<Key>>(records[3])}};
    children[2]->records =
        std::vector<_RecordPtr>{
            {std::make_shared<RecordImpl<Key>>(records[4]),
             std::make_shared<RecordImpl<Key>>(records[5]),
             std::make_shared<RecordImpl<Key>>(records[6])}};

    // sibling
    children[0]->sibling = children[1];
    children[1]->sibling = children[2];

    // attach children to root
    rootNode->childNodes =
        std::vector<_NodePtr>{children};
  }
  void
  TearDown() {}
}; // class TestAscender

TEST_F(TestAscender1, AfterSetUp)
{
  /* check out SetUp() has been complitly finished*/
  ASSERT_EQ(Has::ChildNodes, rootNode->has);
  for (const auto &child : children)
  {
    ASSERT_EQ(Has::RecordPointers, child->has);
  }

  EXPECT_EQ(2, rootNode->keys.size());
  EXPECT_EQ(2, children[0]->records.size());
  EXPECT_EQ(2, children[1]->records.size());
  EXPECT_EQ(3, children[2]->records.size());

  EXPECT_EQ(2, rootNode->childNodes[0]->records.size());
  EXPECT_EQ(2, rootNode->childNodes[1]->records.size());
  EXPECT_EQ(3, rootNode->childNodes[2]->records.size());
}

/// [0,1,2,3] -> split -> [0,1], [2,3]
/// ascend [2,3] result is
/// [2,,]
/// - [0,1,]
/// - [2,3,]
/// retval = [2,,]
TEST_F(TestAscender1, GettersCheck)
{
  auto rootNode = make_shared<bptree::Node<Key>>(Has::RecordPointers);
  auto fakeStack = stack<_NodePtr>{/*empty*/};
  rootNode->records = vector<shared_ptr<_Record>>{
      make_shared<_RecordImpl>(records[0]),
      make_shared<_RecordImpl>(records[1]),
      make_shared<_RecordImpl>(records[2]),
      make_shared<_RecordImpl>(records[3]),
  };
  std::sort(rootNode->records.begin(), rootNode->records.end());
  auto unsaturated = split(*rootNode);
  auto left = make_shared<_Node>(unsaturated.first);
  auto right = make_shared<_Node>(unsaturated.second);
  auto ascender =
      AscenderExtension<Key>(
          right,
          std::move(fakeStack),
          rootNode,
          kMaxKey);

  EXPECT_EQ(nullptr, ascender.parent());
  EXPECT_EQ(right, ascender.descender());
  EXPECT_EQ(right, ascender.ascender());
  EXPECT_TRUE(ascender.history().empty()) << ascender.history().size();
  EXPECT_EQ(rootNode, ascender.cursor());
}
