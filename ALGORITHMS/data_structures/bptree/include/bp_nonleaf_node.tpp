
#include "ranged-compare.hpp"
#include <memory>
#include <array>
#include <optional>
#include <string>
#include <optional>
#include <algorithm>

namespace bptree
{
  using std::array;
  using std::nullopt;
  using std::optional;
  using std::shared_ptr;
  using std::unique_ptr;
  using std::vector;
  using std::weak_ptr;

  template <class K, class R, size_t M>
  class AbstNode;

  template <class K, class R, size_t M>
  class LeafNode;

  template <class K, class R, size_t M>
  class NonLeafNode;

  template <class K, class R, size_t M>
  auto NonLeafNode<K, R, M>::parent() const noexcept -> weak_ptr<Node>
  {
    return mParent;
  }

  template <class K, class R, size_t M>
  auto NonLeafNode<K, R, M>::full() const noexcept -> bool
  {
    return (keyCount() == mKeys.size());
  }

  template <class K, class R, size_t M>
  auto NonLeafNode<K, R, M>::empty() const noexcept -> bool
  {
    return (keyCount() == 0);
  }

  template <class K, class R, size_t M>
  auto NonLeafNode<K, R, M>::validate() const noexcept -> bool
  {
    // is number of children always bigger than keys by 1 except empty?
    const size_t kChildCount = childCount();
    const size_t kKeyCount = keyCount();
    if (empty())
    {
      if (kChildCount == 0)
        return true;
      else
        return false;
    }
    if (kChildCount != kKeyCount + 1)
    {
      return false;
    }
    // TODO: is key sorted?
    for (size_t i = 0; i < kKeyCount - 1; ++i)
    {
      if (mKeys[i + 1] <= mKeys[i])
      {
        return false;
      }
    }
    return true;
  }

  template <class K, class R, size_t M>
  auto NonLeafNode<K, R, M>::keys() const noexcept -> const std::vector<K> &
  {
    return mKeys;
  }

  template <class K, class R, size_t M>
  auto NonLeafNode<K, R, M>::keyCount() const noexcept -> size_t
  {
    return mKeys.size();
  }

  template <class K, class R, size_t M>
  auto NonLeafNode<K, R, M>::insert(K key) -> void
  {
    if (full())
    {
      throw bptree::node_overflow{};
    }
    if (empty())
    {
      doInsert(key, 0);
      return;
    }
    const auto kKeySize = keyCount();
    const auto kKeys = keys();
    doInsert(key, findIdxBy(key));
  }

  template <class K, class R, size_t M>
  auto NonLeafNode<K, R, M>::remove(K key) -> void
  {
  }

  template <class K, class R, size_t M>
  auto NonLeafNode<K, R, M>::childNodes() const noexcept -> const vector<NodePtr> &
  {
    return mChildContainer.childNodes();
  }

  template <class K, class R, size_t M>
  auto NonLeafNode<K, R, M>::childCount() const noexcept -> size_t
  {
    return mChildContainer.childCount();
  }

  template <class K, class R, size_t M>
  auto NonLeafNode<K, R, M>::swapChild(shared_ptr<Node> with, index_t idx) noexcept -> void
  {
    std::swap(mChildContainer.childNodes()[idx], with);
  }

  template <class K, class R, size_t M>
  auto NonLeafNode<K, R, M>::validateChildNodes() const noexcept -> bool
  // Do every key in child nodes fit in a right index?
  // <----------key[0]----------key[1]----------...----------key[m]------------>
  //  (child[0])      [child[1])      [child[2])...[child[m])      [child[m+1])
  //
  // child[i] < key[i] <= child[i+1], i in range[0,keyCount)
  //
  // every child key 'n' in mChildContainer.childNodes() must in range where key index 'i'
  // CASE 0 )
  //   n < key[i]
  //
  // CASE 1...<keyCount - 1 )
  //   key[i] <= n < key[i+1]
  //
  // CASE keyCount )
  //   key[i] <= n
  {
    // 일단 내 key 개수 == child 수 - 1 인 걸 증명하자.
    if (!validate())
    {
      return false;
    }
    // CASE 0 )
    // const auto kChildNodes = std::vector<shared_ptr<Node>>{
    //     [children{childNodes()}]()
    //     {
    //       auto ret = std::vector<shared_ptr<Node>>{};
    //       for (const shared_ptr<Node> n : children)
    //       {
    //         n ? ret.push_back(n): ;
    //       }
    //       return ret;
    //     }()};
    // const auto kMyKeys = std::vector<K>{
    //     [keysArray{keys()}]()
    //     {
    //       auto ret = std::vector<K>{};
    //       for (const optional<K> k : keysArray)
    //       {
    //         k ? ret.push_back(k): ;
    //       }
    //       return ret;
    //     }()};

    // for (const optional<K> &n : kChildKeys0)
    // {
    //   if (n.has_value() && mKeys[0] <= n)
    //   {
    //     return false;
    //   }
    // }
    // // CASE 1..<keyCount )
    // for (size_t i = 1; i < keyCount; ++i)
    // {
    //   const auto kChildKeys = childNodes[i].keys();
    //   for (const optional<K> &n : kChildKeys)
    //   {
    //     if (n.has_value() and not(mKeys[i - 1] <= n && n < mKeys[i]))
    //     {
    //       return false;
    //     }
    //   }
    // }
    //  // CASE keyCount )
    // const vector<K>, M> &kChildKeysLast = childNodes[keyCount].keys();
    // for (const optional<K> &n : kChildKeysLast)
    // {
    //   if (n.has_value() and n < mKeys[keyCount - 1])
    //   {
    //     return false;
    //   }
    // }
    // return true;
  }

  template <class K, class R, size_t M>
  auto NonLeafNode<K, R, M>::findIdxBy(K key) const noexcept -> size_t
  {
    // key가 낑겨들어갈 또는 정확한 위치의 index를 찾기
    // const auto kKeyCount = keyCount();
    // size_t left = 0;
    // size_t right = kKeyCount;
    // size_t idx = static_cast<size_t>((left + right) / 2);
    // while (left < right)
    // {
    //   const auto &k =
    // }
  }

  template <class K, class R, size_t M>
  NonLeafNode<K, R, M>::NonLeafNode(ChildContainable_ &childContainer, weak_ptr<Node> parent)
      : mChildContainer{childContainer}, mKeys{}, mParent{parent}
  {
  }

  template <class K, class R, size_t M>
  NonLeafNode<K, R, M>::~NonLeafNode()
  {
    mKeys.~vector();
    mParent.reset();
  }
} // namespace bptree