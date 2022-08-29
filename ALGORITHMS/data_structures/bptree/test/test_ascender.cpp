#include <bptree.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <stack>

template <class Key>
class AscenderExtension : bptree::Ascender<Key>
{
  using _Ascender = bptree::Ascender<Key>;
  using _Node = bptree::Node<Key>;
  using _NodePtr = std::shared_ptr<_Node>;

public:
  auto parent() const -> _NodePtr { return _Ascender::parent(); }
  auto descender() const -> _NodePtr { return _Ascender::desender(); }
  auto ascender() const -> _NodePtr { return _Ascender::ascender(); }
  auto history() const -> const std::stack<_NodePtr> &
  {
    return _Ascender::history();
  }
  auto cursor() const -> _NodePtr { return _Ascender::cursor(); }
}; // class AscenderExtension

class TestAscender1 : ::testing::Test
{
protected:
    void SetUp()
  {
  }
  void TearDown() {}
}; // class TestAscender