#ifndef FORWARD_DECL
#define FORWARD_DECL

#include <cstddef>

// forward declaration
namespace bptree
{
  using std::size_t;

  constexpr size_t MAX_KEY = 3;
  constexpr size_t MAX_CHILD = MAX_KEY + 1;

  template <class Key>
  struct Record;

  template <class Key>
  class BPTree;

  // Enumeration
  // for distinguishing Leaf and NonLeaf
  enum Has
  {
    ChildNodes,
    RecordPointers,
  };

  template <class Key>
  struct Node;

  template <class Key>
  class TreeFactory;

} // namespace bptree

#endif // FORWARD_DECL