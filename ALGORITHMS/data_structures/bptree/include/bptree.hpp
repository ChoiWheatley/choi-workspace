#ifndef BPTREE
#define BPTREE

#include <memory>
#include <vector>

namespace bptree
{
  using std::shared_ptr;
  using std::unique_ptr;
  using std::vector;

  // <<interface>>
  // Record holds pointer of real data
  template <class Key>
  struct Record
  {
    virtual auto key() -> Key = 0;
    virtual ~Record(){};
  };

  // <<interface>>
  // Do a real logic
  template <class Key>
  class BPTree
  {
  public:
    using R = Record<Key>;

    virtual auto Add(shared_ptr<R> record) -> void = 0;
    virtual auto Delete(Key key) -> void = 0;
    virtual auto Find(Key key) -> /*Nullable*/ R * = 0;

    virtual ~BPTree(){};
  };

  // Enumeration
  // for distinguishing Leaf and NonLeaf
  enum Has
  {
    ChildNodes,
    RecordPointers,
  };

  // <<interface>>
  // Node can hold child nodes OR records
  template <class Key>
  struct Node
  {
    using R = Record<Key>;
    using N_p = shared_ptr<Node>;
    using R_p = shared_ptr<R>;
    /// is Node LeafNode? Non LeafNode?
    virtual auto has() const -> Has = 0;
    virtual auto childNodes() -> vector<N_p> & = 0;
    virtual auto records() -> vector<R_p> & = 0;

    Node(){};
    virtual ~Node(){};
  };

  // <<interface>>
  // abstract factory pattern
  template <class Key>
  class NodeFactory
  {
  public:
    using N = Node<Key>;
    virtual auto makeNode(Has has) const -> unique_ptr<N> = 0;
  }; // class NodeFactory

  template <class Key>
  class TreeFactory
  {
  public:
    using T = BPTree<Key>;
    virtual auto makeTree(size_t childCount) const -> unique_ptr<T> = 0;
  }; // class TreeFactory

} // namespace bptree

#include "bptree.tpp"
#include "node.tpp"

#endif // BPTREE