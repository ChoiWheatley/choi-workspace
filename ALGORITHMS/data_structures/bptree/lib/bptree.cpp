#include <bptree.hpp>

namespace bptree
{
  class BPTreeImpl : public BPTree
  {
  public:
    auto Add(Key key, shared_ptr<Record> record) -> void override;
    auto Delete(Key key) -> void override;
    auto Find(Key key) -> /*Nullable*/ Record * override;

  private:
    unique_ptr<Node> rootNode = nullptr;
  }; // class BPTreeImpl
} // namespace bptree

/// Implementation
namespace bptree
{
  auto BPTreeImpl::Add(Key key, shared_ptr<Record> record) -> void
  {
    // TODO: impl
  }
} // namespace bptree