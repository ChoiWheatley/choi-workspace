#ifndef BPTREE_BPTREE
#define BPTREE_BPTREE

#include "bp_error.hpp"
#include "bp_helpers.hpp"
#include <array>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

namespace bptree
{
  using std::array;
  using std::nullopt;
  using std::optional;
  using std::shared_ptr;
  using std::unique_ptr;
  using std::vector;
  using std::weak_ptr;

  using index_t = size_t;

  /*
  forward declarations
  */

  template <class K, class R, size_t M>
  class AbstNode;

  template <class K, class R, size_t M>
  class LeafNode;

  template <class K, class R, size_t M>
  class NonLeafNode;

  template <class K, class R, size_t M>
  class BPFactory;

  template <class K, class R, size_t M>
  class ChildContainable;

  template <class K, class R, size_t M>
  class ChildContainer;
}; // namespace bptree

#include "bp_abst_node.tpp"
#include "bp_child_container.tpp"
#include "bp_factory.tpp"
#include "bp_leaf_node.tpp"
#include "bp_nonleaf_node.tpp"
#include "bptree.tpp"

#endif // BPTREE_BPTREE
