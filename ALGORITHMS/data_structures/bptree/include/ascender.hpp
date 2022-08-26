#ifndef ASCENDER
#define ASCENDER

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
  using std::stack;
  using std::vector;

  template <class Key>
  class Ascender
  {
    using _Node = Node<Key>;
    using _NodePtr = shared_ptr<_Node>;
    using _Record = Record<Key>;
    using _RecordPtr = shared_ptr<_Record>;

    const vector<_RecordPtr> &ascender_;
    stack<_NodePtr> history_;
    _NodePtr cursor_;

    _NodePtr parent_ = nullptr;
    _NodePtr descender_ = nullptr;

  public:
    /// do ascend, recursiveness if saturated is true
    /// NOTE: every parents are Non-leaf nodes.
    /// parent:     {30,__,__}
    /// ascender:   {20,25,__}
    /// newParent:  {20,30,__}
    /// childNodes: {{},{20,25,__},{},__}
    /// index where key insert: 0
    /// index where child insert: 1
    auto Ascend() -> void
    {
      _Node newParent{Has::ChildNodes};
      if (parent())
      {
        newParent = _Node{*parent()};
        // vector<Key> keys = newParent.keys;
        // vector<_NodePtr> &childNodes = newParent.childNodes;

        const Key ascendKey = ascender_.front()->key();
        const size_t nextIndex = findIndexBetween(newParent.keys, ascendKey);
        // push key back from index `nextIndex`
        newParent.keys.insert(newParent.keys.begin() + nextIndex, ascendKey);
        // push descender node from index `nextIndex`+1
        newParent.childNodes.insert(newParent.childNodes.begin() + nextIndex + 1, descender_);

        // COMMIT
        parent() = std::make_shared<_Node>(newParent);
      }
      else
      // cursor was root
      {
        newParent.childNodes.push_back(cursor_);
        // TODO: impl
      }
    }

    // pop from history stack and cache it
    auto parent() -> /*Nullable*/ _NodePtr
    {
      if (history_.empty())
      {
        return nullptr;
      }
      if (!parent_)
      {
        parent_ = history_.top();
        history_.pop();
      }
      return parent_;
    }

    Ascender(const vector<_RecordPtr> &ascender,
             stack<_NodePtr> &&history,
             _NodePtr cursor)
        : ascender_{ascender},
          history_{history},
          cursor_{cursor}
    {
      descender_ = std::make_shared<_Node>(Has::RecordPointers);
      descender_->records = ascender_;
    }

  private:
    auto isSaturated() -> bool
    {
      return (MAX_KEY < parent()->keys.size());
    }
  }; // class Ascender
} // namespace bptree

#endif // ASCENDER