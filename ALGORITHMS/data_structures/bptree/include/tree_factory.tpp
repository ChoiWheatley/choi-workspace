#include "forward_decl.hpp"
#include <memory>

namespace bptree
{
  using std::unique_ptr;

  // <<interface>>
  // abstract factory pattern
  template <class Key>
  class TreeFactory
  {
  public:
    using T = BPTree<Key>;
    virtual auto makeTree(size_t childCount) const -> unique_ptr<T> = 0;
  }; // class TreeFactory

}