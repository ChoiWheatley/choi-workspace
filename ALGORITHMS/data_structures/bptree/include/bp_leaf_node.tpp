#include <array>
#include <cmath>
#include <memory>
#include <optional>
#include <string>

namespace bptree
{
  using std::array;
  using std::nullopt;
  using std::optional;
  using std::pair;
  using std::shared_ptr;
  using std::unique_ptr;
  using std::weak_ptr;

  template <class K, class R, size_t M>
  class AbstNode;

  template <class K, class R, size_t M>
  class LeafNode;

  template <class K, class R, size_t M>
  class NonLeafNode;

  template <class K, class R, size_t M>
  auto LeafNode<K, R, M>::parent() const noexcept -> weak_ptr<Node>
  {
    return mParent;
  }

  template <class K, class R, size_t M>
  auto LeafNode<K, R, M>::full() const noexcept -> bool
  {
    return (keyCount() == M);
  }

  template <class K, class R, size_t M>
  auto LeafNode<K, R, M>::empty() const noexcept -> bool
  {
    return (keyCount() == 0);
  }

  template <class K, class R, size_t M>
  auto LeafNode<K, R, M>::insert(shared_ptr<R> record, K key) -> void
  {
    if (full())
    {
      throw bptree::node_overflow{};
    }
    if (empty())
    {
      doInsert(std::move(record), key, 0);
      return;
    }
    // key가 낑겨들어갈 index를 찾기
    doInsert(std::move(record), key, minIdxLargerThan(key, keys(), false));
  }

  template <class K, class R, size_t M>
  auto LeafNode<K, R, M>::keys() const noexcept -> const vector<K> &
  {
    return mKeys;
  }

  template <class K, class R, size_t M>
  auto LeafNode<K, R, M>::keyCount() const noexcept -> size_t
  {
    return mKeys.size();
  }

  template <class K, class R, size_t M>
  auto LeafNode<K, R, M>::validate() const noexcept -> bool
  {
    if (empty())
    {
      return true;
    }
    auto flag = (keyCount() == recordCount());
    // is key sorted?
    for (size_t i = 0; i < keyCount() - 1; ++i)
    {
      if (mKeys[i + 1] < mKeys[i])
      {
        flag = false;
        break;
      }
    }

    return flag;
  }

  template <class K, class R, size_t M>
  auto LeafNode<K, R, M>::records() const noexcept -> const vector<RecordPtr> &
  {
    return mRecordPointers;
  }

  template <class K, class R, size_t M>
  auto LeafNode<K, R, M>::recordCount() const noexcept -> size_t
  {
    return mRecordPointers.size();
  }

  template <class K, class R, size_t M>
  auto LeafNode<K, R, M>::remove(K key) -> void
  {
    if (empty())
    {
      throw bptree::node_underflow{};
    }
    const auto left = maxIdxLessThan(key, keys(), true);
    const auto right = minIdxLargerThan(key, keys(), false);
    for (auto i = left; i < right; ++i)
    {
      doRemove(left);
    }
    // const auto size = keyCount();
    // size_t left = 0;
    // size_t right = size;
    // size_t idx = static_cast<size_t>((left + right) / 2);
    // while (left < right)
    // {
    //   const auto &val = mKeys.at(idx);
    //   if (val < key)
    //   // move right
    //   {
    //     left = (left == idx) ? (left + 1) : idx;
    //   }
    //   else if (key < val)
    //   // move left
    //   {
    //     right = (right == idx) ? (right - 1) : idx;
    //   }
    //   else /* key == *val */
    //   {
    //     doRemove(idx);
    //   }
    //   idx = static_cast<size_t>((left + right) / 2);
    // }
  }

  template <class K, class R, size_t M>
  auto LeafNode<K, R, M>::sibling() -> shared_ptr<LeafNode>
  {
    return mSibling;
  }

  template <class K, class R, size_t M>
  auto LeafNode<K, R, M>::attach(shared_ptr<LeafNode> sibling)
  {
    mSibling = sibling;
  }

  template <class K, class R, size_t M>
  auto LeafNode<K, R, M>::detachSibling()
  {
    mSibling.reset();
  }

  template <class K, class R, size_t M>
  LeafNode<K, R, M>::LeafNode(weak_ptr<AbstNode<K, R, M>> parent, shared_ptr<LeafNode<K, R, M>> sibling)
      : mKeys{},
        mRecordPointers{},
        mParent{parent},
        mSibling{sibling} {}

  template <class K, class R, size_t M>
  LeafNode<K, R, M>::LeafNode()
      : mKeys{},
        mRecordPointers{},
        mParent{},
        mSibling{} {}

  template <class K, class R, size_t M>
  LeafNode<K, R, M>::LeafNode(LeafNode &&other)
  {
    this->mKeys = other.mKeys;
    this->mRecordPointers = other.mRecordPointers;
    this->mParent = other.mParent;
    this->mSibling = other.mSibling;
  }

  template <class K, class R, size_t M>
  LeafNode<K, R, M>::~LeafNode() {}

  template <class K, class R, size_t M>
  auto LeafNode<K, R, M>::doInsert(shared_ptr<R> record, K key, size_t idx)
  {
    mKeys.insert(mKeys.begin() + idx, key);
    mRecordPointers.insert(mRecordPointers.begin() + idx, record);
  }

  template <class K, class R, size_t M>
  auto LeafNode<K, R, M>::doRemove(size_t idx)
  {
    mKeys.erase(mKeys.begin() + idx);
    mRecordPointers.erase(mRecordPointers.begin() + idx);
  }
} // namespace bptree