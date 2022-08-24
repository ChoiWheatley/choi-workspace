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

    virtual auto Add(Key key, shared_ptr<R> record) -> void = 0;
    virtual auto Delete(Key key) -> void = 0;
    virtual auto Find(Key key) -> /*Nullable*/ R * = 0;

    virtual ~BPTree() = 0;
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
    virtual auto has() const -> Has = 0;
    virtual auto childNodes() -> vector<N_p> & = 0;
    virtual auto records() -> vector<R_p> & = 0;

    virtual ~Node() = 0;
  };

} // namespace bptree

#include "bptree.tpp"