#include "forward_decl.hpp"
#include "helpers.hpp"
#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>

namespace bptree
{
  using std::shared_ptr;
  using std::unique_ptr;
  using std::vector;

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

  template <class Key>
  class BPTreeImpl : public BPTree<Key>
  {
    using _Node = Node<Key>;
    using _Record = Record<Key>;

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
      // Tour until leaf node
      _Node *cursor = rootNode.get();
      while (cursor->has != RecordPointers)
      {
        const auto nextIndex = findIndexBetween(
            cursor->childKeys(),
            record->key());
        cursor = cursor->childNodes[nextIndex].get();
      }
      assert(cursor->has == RecordPointers);
      assert(!cursor->records.empty());
      // push new record no matter it exceeds
      cursor->records.push_back(record);
      std::sort(cursor->records.begin(), cursor->records.end());
      // size exceeds control
      if (MAX_KEY < cursor->records.size())
      {
        // TODO: impl
      }
    }

    auto Delete(Key key) -> void override
    {
      // TODO: impl
    }
    auto Find(Key key) -> /*Nullable*/ _Record * override
    {
      // TODO: impl
    }

    BPTreeImpl() = default;
    BPTreeImpl(const BPTreeImpl &other) = delete;
    BPTreeImpl(BPTreeImpl &&other) = delete;
    ~BPTreeImpl(){};
  }; // class BPTreeImpl

} // namespace bptree
