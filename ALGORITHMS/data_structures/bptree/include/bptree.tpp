#include "ascender.hpp"
#include "forward_decl.hpp"
#include "helpers.hpp"
#include "node.tpp"
#include "record.tpp"
#include <algorithm>
#include <cassert>
#include <memory>
#include <stack>
#include <vector>

namespace bptree
{
  using std::shared_ptr;
  using std::stack;
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
    using _NodePtr = shared_ptr<_Node>;
    using _Record = Record<Key>;
    using _RecordPtr = shared_ptr<_Record>;

    _NodePtr rootNode = nullptr;

  public:
    auto Add(shared_ptr<_Record> record) -> void override
    {
      if (!rootNode)
      {
        rootNode = std::make_unique<_Node>(RecordPointers);
        rootNode->records.push_back(record);
        return;
      }

      // Tour until leaf node
      stack<_NodePtr> history{};
      _NodePtr cursor = rootNode;
      while (cursor->has != RecordPointers)
      {
        history.push(cursor);
        const auto nextIndex = findIndexBetween(
            cursor->keys,
            record->key());
        cursor = cursor->childNodes[nextIndex];
      }

      assert(cursor->has == RecordPointers);
      assert(!cursor->records.empty());

      _NodePtr const oldSibling = cursor->sibling;
      _NodePtr newCursor = std::make_shared<_Node>(Has::RecordPointers);
      newCursor->records = vector<_RecordPtr>(cursor->records); // copy ctor?

      // push new record no matter it exceeds
      newCursor->records.push_back(record);
      std::sort(newCursor->records.begin(), newCursor->records.end());

      // size exceeds control
      if (isSaturated(*newCursor))
      {
        // unsaturate big chunk and ascend the bigger one
        auto unsaturated = split(*newCursor);

        // find ascender and do ascend
        _NodePtr const ascender = std::make_shared<_Node>(unsaturated.second);
        _NodePtr newRoot = Ascender<Key>(ascender, std::move(history), cursor).Ascend();

        // commit
        if (newRoot)
        {
          // depth + 1
          rootNode = std::move(newRoot);
        }
        _Node newSibling = std::move(unsaturated.second);
        newCursor = std::make_shared<_Node>(std::move(unsaturated.first));
        newCursor->sibling = std::make_shared<_Node>(std::move(newSibling));
        newSibling.sibling = oldSibling;
      }

      // commit
      cursor = std::move(newCursor);
    } // Add

    auto Delete(Key key) -> void override
    {
      // TODO: impl
    } // Delete

    auto Find(Key key) -> /*Nullable*/ _Record * override
    {
      // TODO: impl
    } // Find

    BPTreeImpl() = default;
    BPTreeImpl(const BPTreeImpl &other) = delete;
    BPTreeImpl(BPTreeImpl &&other) = delete;
    ~BPTreeImpl(){};

  private:
  }; // class BPTreeImpl

} // namespace bptree
