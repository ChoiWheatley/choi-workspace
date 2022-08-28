#ifndef REAL_FACTORY
#define REAL_FACTORY

#include <bptree.hpp>

using namespace bptree;

template <class Key>
class RealFactory
    : public bptree::TreeFactory<Key>
{
  using T = BPTree<Key>;
  using T_Impl = BPTreeImpl<Key>;

public:
  auto makeTree(size_t childCount) const -> unique_ptr<T> override
  {
    return std::make_unique<T_Impl>();
  }
}; // class RealFactory

#endif // REAL_FACTORY