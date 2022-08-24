#include <memory>
#include <vector>

namespace bptree
{
  template <class Key>
  class BPTreeImpl : public BPTree<Key>
  {
    using R = Record<Key>;

    unique_ptr<Node<Key>> rootNode = nullptr;

  public:
    auto Add(shared_ptr<Record<Key>> record) -> void override
    {
      if (!rootNode)
      {
        rootNode = std::make_unique<Node<Key>>(RecordPointers);
        rootNode->records.push_back(record);
        return;
      }
      auto cursor = rootNode.get();
      while (cursor->has != RecordPointers)
      {
      }
    }
    auto Delete(Key key) -> void override
    {
      // TODO: impl
    }
    auto Find(Key key) -> /*Nullable*/ R * override
    {
      // TODO: impl
    }

    BPTreeImpl() = default;
    BPTreeImpl(const BPTreeImpl &other) = delete;
    BPTreeImpl(BPTreeImpl &&other) = delete;
    ~BPTreeImpl(){};
  }; // class BPTreeImpl

} // namespace bptree
