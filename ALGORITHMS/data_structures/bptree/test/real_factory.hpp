#include <bptree.hpp>

using namespace bptree;

template <class Key>
class RealFactory
    : public bptree::NodeFactory<Key>,
      public bptree::TreeFactory<Key>
{
  using N = Node<Key>;
  using N_Impl = NodeImpl<Key>;
  using T = BPTree<Key>;
  using T_Impl = BPTreeImpl<Key>;

public:
  auto makeNode(Has has) const -> unique_ptr<N> override
  {
    return std::make_unique<N_Impl>(has);
  }
  auto makeTree(size_t childCount) const -> unique_ptr<T> override
  {
    return std::make_unique<T_Impl>(
        std::make_unique<RealFactory<Key>>(
            *this));
  }
}; // class RealFactory