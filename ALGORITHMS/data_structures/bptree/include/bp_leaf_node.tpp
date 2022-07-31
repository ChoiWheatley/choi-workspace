#include <memory>
#include <array>
#include <optional>
#include <string>
#include <optional>

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
    const auto size = keySize();
    // key가 낑겨들어갈 index를 찾기
    size_t idx = static_cast<size_t>(size / 2);
    size_t remain = size;
    while (1 <= remain)
    {
      if (mKeys.at(idx).value() < key)
      {
        idx = static_cast<size_t>((idx + size) / 2);
      }
      else
      {
        idx = static_cast<size_t>(idx / 2);
      }
      remain = static_cast<size_t>(remain / 2);
    }
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
        mKeys.at(i) = mKeys.at(i - 1);
        mRecordPointers.at(i) = mRecordPointers.at(i - 1);
      }
      mKeys.at(idx) = key;
      mRecordPointers.at(idx) = std::move(record);
      return;
    }
  }

  template <class K, class R, size_t M>
  auto LeafNode<K, R, M>::remove(K key) -> void
  {
    if (empty())
    {
      throw bptree::node_is_empty{};
    }
    auto found = false;
    const auto size = keySize();
    size_t idx = static_cast<size_t>(size / 2);
    size_t remain = size;
    while (1 <= remain)
    {
      if (mKeys.at(idx).value() < key)
      {
        idx = static_cast<size_t>((idx + size) / 2);
      }
      else if (key < mKeys.at(idx).value())
      {
        idx = static_cast<size_t>(idx / 2);
      }
      else
      {
        found = true;
        break;
      }
    }
    if (found)
    {
      mKeys.at(idx).reset();
      mRecordPointers.at(idx).reset();
      // 나머지들을 앞으로 땡겨줘야 함.
      for (size_t i = idx; i < size - 1; ++i)
      {
        mKeys.at(i) = mKeys.at(i + 1);
        mRecordPointers.at(i) = mRecordPointers.at(i + 1);
      }
      mKeys.at(size).reset();
      mRecordPointers.at(size).reset();
      return;
    }
    else
    {
      throw bptree::no_key_found{};
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
    return (keySize() == recordPointerSize());
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

} // namespace bptree