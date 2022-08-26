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
    using _Record = Record<Key>;
    using _RecordPtr = shared_ptr<_Record>;

    unique_ptr<_Node> rootNode = nullptr;

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
      stack<_Node *> history{};
      _Node *cursor = rootNode.get();
      while (cursor->has != RecordPointers)
      {
        history.push(cursor);
        const auto nextIndex = findIndexBetween(
            cursor->childKeys(),
            record->key());
        cursor = cursor->childNodes[nextIndex].get();
      }

      assert(cursor->has == RecordPointers);
      assert(!cursor->records.empty());

      const shared_ptr<_Node> oldSibling = cursor->sibling;
      auto newRecords = vector<_RecordPtr>(cursor->records);

      // push new record no matter it exceeds
      newRecords.push_back(record);
      std::sort(newRecords.begin(), newRecords.end());

      // size exceeds control
      if (isSaturated(cursor))
      {
        // unsaturate big chunk and ascend the bigger one
        auto unsaturated = split(newRecords);

        auto newSibling = std::make_shared<_Node>(Has::RecordPointers);
        newSibling->records = std::move(unsaturated.first);

        newRecords = std::move(unsaturated.second);
        cursor->sibling = newSibling;
        newSibling->sibling = oldSibling;
      }

      // commit
      cursor->records = std::move(newRecords);
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

  private:
    auto isSaturated(_Node *node) -> bool
    {
      return (MAX_KEY < node->records.size());
    }
    auto isSaturated(vector<_RecordPtr> records) -> bool
    {
      return (MAX_KEY < records.size());
    }
  }; // class BPTreeImpl

} // namespace bptree
