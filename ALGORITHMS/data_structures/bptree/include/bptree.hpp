#include <memory>
#include <vector>

namespace bptree
{
  using std::shared_ptr;
  using std::unique_ptr;
  using std::vector;

  // <<interface>>
  // Holds key value
  struct Key
  {
  };

  // <<interface>>
  // Record holds pointer of real data
  struct Record
  {
    virtual auto key() -> /*Non-Null*/ Key * = 0;
    virtual ~Record(){};
  };

  // <<interface>>
  // Do a real logic
  class BPTree
  {
  public:
    virtual auto Add(Key key, shared_ptr<Record> record) -> void = 0;
    virtual auto Delete(Key key) -> void = 0;
    virtual auto Find(Key key) -> /*Nullable*/ Record * = 0;

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
  struct Node
  {
    using N_p = shared_ptr<Node>;
    using R_p = shared_ptr<Record>;
    virtual auto has() const -> Has = 0;
    virtual auto childNodes() -> vector<N_p> & = 0;
    virtual auto records() -> vector<R_p> & = 0;

    virtual ~Node() = 0;
  };

} // namespace bptree