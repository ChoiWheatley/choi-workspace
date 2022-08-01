#include <memory>
#include <array>
#include <optional>
#include <string>
#include <optional>
#include <cmath>

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
  auto LeafNode<K, R, M>::keys() const noexcept -> const array<optional<K>, M> &
  {
    return mKeys;
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
    const auto size = keySize();
    // key가 낑겨들어갈 index를 찾기
    size_t left = 0;
    size_t right = size;
    size_t idx = static_cast<size_t>((left + right) / 2);
    while (left < right)
    {
      const auto &optVal = mKeys.at(idx);
      if (!optVal)
      {
        break;
      }
      if (optVal.value() < key)
      // move right
      {
        left = (left == idx) ? (left + 1) : idx;
      }
      else
      // move left
      {
        right = (right == idx) ? (right - 1) : idx;
      }
      idx = static_cast<size_t>((left + right) / 2);
    }
    doInsert(std::move(record), key, idx);
  }

  template <class K, class R, size_t M>
  auto LeafNode<K, R, M>::remove(K key) -> void
  {
    if (empty())
    {
      throw bptree::node_underflow{};
    }
    const auto size = keySize();
    size_t left = 0;
    size_t right = size;
    size_t idx = static_cast<size_t>((left + right) / 2);
    while (left < right)
    {
      const auto &optVal = mKeys.at(idx);
      if (!optVal)
      {
        break;
      }
      if (*optVal < key)
      // move right
      {
        left = (left == idx) ? (left + 1) : idx;
      }
      else if (key < *optVal)
      // move left
      {
        right = (right == idx) ? (right - 1) : idx;
      }
      else /* key == *optVal */
      {
        doRemove(key, idx);
      }
      idx = static_cast<size_t>((left + right) / 2);
    }
  }

  template <class K, class R, size_t M>
  auto LeafNode<K, R, M>::parent() const noexcept -> weak_ptr<Node>
  {
    return mParent;
  }

  template <class K, class R, size_t M>
  auto LeafNode<K, R, M>::full() const noexcept -> bool
  {
    return (keySize() == mKeys.size());
  }

  template <class K, class R, size_t M>
  auto LeafNode<K, R, M>::empty() const noexcept -> bool
  {
    return (keySize() == 0);
  }

  template <class K, class R, size_t M>
  auto LeafNode<K, R, M>::keySize() const noexcept -> size_t
  {
    for (size_t cnt = 0; cnt < mKeys.size(); ++cnt)
    {
      if (!mKeys[cnt].has_value())
      {
        return cnt;
      }
    }
    return mKeys.size();
  }

  template <class K, class R, size_t M>
  auto LeafNode<K, R, M>::validate() const noexcept -> bool
  {
    auto flag = (keySize() == recordPointerSize());
    if (empty())
    {
      return true;
    }
    // is key sorted?
    for (size_t i = 0; i < keySize() - 1; ++i)
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
  auto LeafNode<K, R, M>::recordPointers() const noexcept -> const array<RecordPTR, M> &
  {
    return mRecordPointers;
  }

  template <class K, class R, size_t M>
  auto LeafNode<K, R, M>::recordPointerSize() const noexcept -> size_t
  {
    for (size_t cnt = 0; cnt < mRecordPointers.size(); ++cnt)
    {
      if (!mRecordPointers[cnt].has_value())
      {
        return cnt;
      }
    }
    return mRecordPointers.size();
  }

  template <class K, class R, size_t M>
  LeafNode<K, R, M>::~LeafNode() {}

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
  auto LeafNode<K, R, M>::doInsert(shared_ptr<R> record, K key, size_t idx)
  {
    const auto size = keySize();
    if (size <= idx)
    {
      // 어차피 이 뒤는 전부 nullopt임.
      mKeys.at(idx) = key;
      mRecordPointers.at(idx) = std::move(record);
      return;
    }
    else
    {
      // 뒤로 땡겨줘야 함. key, recordPointer 둘 다
      for (size_t i = size; i > idx; --i)
      {
        mKeys.at(i).swap(mKeys.at(i - 1));
        mRecordPointers.at(i).swap(mRecordPointers.at(i - 1));
      }
      mKeys.at(idx) = key;
      mRecordPointers.at(idx) = std::move(record);
      return;
    }
  }

  template <class K, class R, size_t M>
  auto LeafNode<K, R, M>::doRemove(K key, size_t idx)
  {
    const auto size = keySize();
    mKeys.at(idx).reset();
    mRecordPointers.at(idx).reset();
    // 나머지들을 앞으로 땡겨줘야 함.
    for (size_t i = idx; i < size - 1; ++i)
    {
      mKeys.at(i).swap(mKeys.at(i + 1));
      mRecordPointers.at(i).swap(mRecordPointers.at(i + 1));
    }
    mKeys.at(size - 1).reset();
    mRecordPointers.at(size - 1).reset();
  }
} // namespace bptree