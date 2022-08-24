#include <memory>
#include <vector>

namespace bptree
{
  template <class Key>
  class BPTreeImpl : public BPTree<Key>
  {
    using R = Record<Key>;
    using N = Node<Key>;
    using F = NodeFactory<Key>;

    unique_ptr<N> rootNode = nullptr;
    const F &nodeFactory;

  public:
    auto Add(shared_ptr<Record<Key>> record) -> void override
    {
      if (!rootNode)
      {
        rootNode = nodeFactory.makeNode(Has::RecordPointers);
        rootNode->records().push_back(record);
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

    BPTreeImpl(const F &concreteFactory)
        : nodeFactory{concreteFactory} {};
    BPTreeImpl(const BPTreeImpl &other) = delete;
    BPTreeImpl(BPTreeImpl &&other) = delete;
    ~BPTreeImpl(){};
  }; // class BPTreeImpl

} // namespace bptree
