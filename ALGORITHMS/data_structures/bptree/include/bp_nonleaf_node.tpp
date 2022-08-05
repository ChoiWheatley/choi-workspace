
#include "ranged-compare.hpp"
#include <algorithm>
#include <array>
#include <memory>
#include <optional>
#include <string>

namespace bptree
{
  using std::array;
  using std::nullopt;
  using std::optional;
  using std::shared_ptr;
  using std::unique_ptr;
  using std::vector;
  using std::weak_ptr;

  /*
  NonLeafNode
    중복을 허용하지 않는 Key
    validate 할 때에만 childNodes의 key를 비교하지, insert, remove에는
    자기가 저장하고 있는 key만 수정한다.
  */
  template <class K, class R, size_t M>
  class NonLeafNode : public AbstNode<K, R, M>
  {
  public:
    using Node = typename bptree::AbstNode<K, R, M>;
    using NodePtr = shared_ptr<Node>;
    using ChildContainable_ = typename bptree::ChildContainable<K, R, M>;
    using ChildContainablePtr = shared_ptr<ChildContainable_>;

    auto parent() const noexcept -> weak_ptr<Node> override;
    auto full() const noexcept -> bool override;
    auto empty() const noexcept -> bool override;
    auto validate() const noexcept -> bool override;
    auto keys() const noexcept -> const vector<K> & override;
    auto keyCount() const noexcept -> size_t override;

    auto insert(K key) -> void;
    auto remove(K key) -> void;
    auto childNodes() const noexcept -> const vector<optional<NodePtr>> &;
    auto childCount() const noexcept -> size_t;
    auto attach(NodePtr child) -> void;
    auto detachChildBy(index_t idx) -> NodePtr;
    auto swapChild(NodePtr with, index_t idx) noexcept -> void;
    auto validateChildNodes() const -> bool;
    auto doInsert(K key, index_t idx) -> void;
    auto doRemove(index_t idx) -> void;

    NonLeafNode(ChildContainablePtr childContainer, weak_ptr<Node> parent = NodePtr{});
    ~NonLeafNode() override;

  private:
    ChildContainablePtr mChildContainer;
    vector<K> mKeys;
    weak_ptr<Node> mParent;
  };

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
    return (keyCount() == M);
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
    doInsert(key, minIdxLargerThan(key, keys(), false));
  }

  template <class K, class R, size_t M>
  auto NonLeafNode<K, R, M>::remove(K key) -> void
  {
    if (empty())
    {
      throw bptree::node_underflow{};
    }
    doRemove(maxIdxLessThan(key, keys(), true));
  }

  template <class K, class R, size_t M>
  auto NonLeafNode<K, R, M>::childNodes() const noexcept -> const vector<optional<NodePtr>> &
  {
    return mChildContainer->childNodes();
  }

  template <class K, class R, size_t M>
  auto NonLeafNode<K, R, M>::childCount() const noexcept -> size_t
  {
    return mChildContainer->childCount();
  }

  template <class K, class R, size_t M>
  auto NonLeafNode<K, R, M>::attach(NodePtr child) -> void
  {
    mChildContainer->attach(child, keys());
  }

  template <class K, class R, size_t M>
  auto NonLeafNode<K, R, M>::detachChildBy(index_t idx) -> NodePtr
  {
    return mChildContainer->detachChildBy(idx);
  }

  template <class K, class R, size_t M>
  auto NonLeafNode<K, R, M>::swapChild(shared_ptr<Node> with, index_t idx) noexcept -> void
  {
    mChildContainer->swapChild(with, idx);
  }

  template <class K, class R, size_t M>
  auto NonLeafNode<K, R, M>::validateChildNodes() const -> bool
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
  auto NonLeafNode<K, R, M>::doInsert(K key, index_t idx) -> void
  {
    mKeys.insert(mKeys.begin() + idx, key);
  }

  template <class K, class R, size_t M>
  auto NonLeafNode<K, R, M>::doRemove(index_t idx) -> void
  {
    mKeys.erase(mKeys.begin() + idx);
  }

  template <class K, class R, size_t M>
  NonLeafNode<K, R, M>::NonLeafNode(ChildContainablePtr childContainer, weak_ptr<Node> parent)
      : mChildContainer{childContainer}, mKeys{}, mParent{parent} {}

  template <class K, class R, size_t M>
  NonLeafNode<K, R, M>::~NonLeafNode()
  {
  }
} // namespace bptree