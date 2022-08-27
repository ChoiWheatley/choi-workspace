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

    const _NodePtr ascender_;
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
    /// childNodes: {{cursor},{20,25,__},{},__}
    /// index where key insert: 0
    /// index where child insert: 1
    auto Ascend() -> _NodePtr
    {
      _NodePtr newParent = std::make_shared<_Node>(Has::ChildNodes);
      if (parent())
      {
        assert(parent()->has == ChildNodes);

        newParent->keys = vector<Key>(parent()->keys);                  // copy ctor
        newParent->childNodes = vector<_NodePtr>(parent()->childNodes); // copy ctor

        const Key ascendKey = ascender_->keys.front();
        const size_t nextIndex = findIndexBetween(newParent->keys, ascendKey);
        // push key back from index `nextIndex`
        newParent->keys.insert(newParent->keys.begin() + nextIndex, ascendKey);
        // push descender node from index `nextIndex`+1
        newParent->childNodes.insert(newParent->childNodes.begin() + nextIndex + 1, descender());

        // size exceeds control
        if (MAX_KEY < newParent->keys.size())
        {
          // unsaturate big chunk and ascend the second one
          auto const unsaturated = split(*newParent);

          // find ascender and do ascend
          _NodePtr const ascender = std::make_shared<_Node>(unsaturated.second);
          _NodePtr const root = Ascender(ascender, std::move(history_), cursor_).Ascend();

          // COMMIT
          return root;
        }

        // COMMIT
        parent() = std::move(newParent);
      }
      else
      // cursor was root
      {
        newParent->childNodes.push_back(cursor_);
        // TODO: impl
      }
      return nullptr;
    }

  protected:
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

    auto descender() -> _NodePtr
    {
      switch (cursor_->has)
      {
      case Has::RecordPointers:
        return ascender_;
      case Has::ChildNodes:
        // descend except ascender's first child
        // BECAUSE: non-leaf nodes are sparse index
        {
          _NodePtr ret = std::make_shared<_Node>(Has::ChildNodes);
          ret->childNodes = vector<_NodePtr>(
              ascender_->childNodes.begin() + 1,
              ascender_->childNodes.end());
          return ret;
        }
      }
    }

    auto ascender() const -> _NodePtr { return ascender_; }
    auto history() const -> stack<_NodePtr> { return history_; }
    auto cursor() const -> _NodePtr { return cursor_; }

  public:
    Ascender(const _NodePtr ascender,
             stack<_NodePtr> &&history,
             _NodePtr cursor)
        : ascender_{ascender},
          history_{history},
          cursor_{cursor}
    {
    }

  private:
  }; // class Ascender
} // namespace bptree

#endif // ASCENDER