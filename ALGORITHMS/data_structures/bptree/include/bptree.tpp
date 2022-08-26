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

      const _NodePtr oldSibling = cursor->sibling;
      auto newRecords = vector<_RecordPtr>(cursor->records); // copy ctor?

      // push new record no matter it exceeds
      newRecords.push_back(record);
      std::sort(newRecords.begin(), newRecords.end());

      // size exceeds control
      if (isSaturated(newRecords))
      {
        // unsaturate big chunk and ascend the bigger one
        auto unsaturated = split(newRecords);

        // TODO: find ascender and do ascend
        const auto &ascender = unsaturated.second;
        Ascender<Key>(ascender, std::move(history), cursor).Ascend();

        // commit
        auto newSibling = std::make_shared<_Node>(Has::RecordPointers);
        newSibling->records = std::move(unsaturated.first);

        newRecords = std::move(unsaturated.second);
        cursor->sibling = newSibling;
        newSibling->sibling = oldSibling;
      }

      // commit
      cursor->records = std::move(newRecords);
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
    auto isSaturated(_Node *node) -> bool
    {
      switch (node->has)
      {
      case Has::ChildNodes:
        return (MAX_KEY < node->keys.size());
      case Has::RecordPointers:
        return (MAX_KEY < node->records.size());
      }
    }
    auto isSaturated(const vector<_RecordPtr> &records) -> bool
    {
      return (MAX_KEY < records.size());
    }
  }; // class BPTreeImpl

} // namespace bptree
