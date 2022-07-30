#ifndef BPTREE_BPTREE
#define BPTREE_BPTREE

#include <memory>
#include <array>
#include <optional>
#include "bp_error.hpp"

namespace bptree
{
  using std::array;
  using std::optional;
  using std::shared_ptr;
  using std::unique_ptr;
  using std::weak_ptr;

  /*
  BPTree
  */
  template <class Key, class Record, size_t M>
  class BPTree
  {
  public:
    auto insert(shared_ptr<Record> record, Key key);
    auto remove(Key key);
    auto query(Key key) const noexcept -> optional<Record>;
    auto size() const noexcept -> size_t;
    // TODO: BPTree iterator 만들어보기

    class AbstNode;

    BPTree();

  private:
    shared_ptr<AbstNode> mRoot;
    size_t mSizeCache = 0;
  };

  /*
  AbstNode
  */
  template <class K, class R, size_t M>
  class BPTree<K, R, M>::AbstNode
  {
  public:
    using Node = typename BPTree<K, R, M>::AbstNode;

    virtual auto keys() const noexcept -> const array<K, M> & = 0;
    virtual auto insert(shared_ptr<R> &&record, K key) -> void = 0;
    virtual auto remove(K key) -> void = 0;
    virtual auto parent() const noexcept -> weak_ptr<Node> = 0;
    virtual auto full() const noexcept -> bool = 0;
    virtual ~AbstNode() = 0;
  };

  /*
  LeafNode
  */
  template <class K, class R, size_t M>
  class LeafNode : public BPTree<K, R, M>::AbstNode
  {
  public:
    using Node = typename BPTree<K, R, M>::AbstNode;

    auto keys() const noexcept -> const array<K, M> & override;
    auto insert(shared_ptr<R> &&record, K key) -> void override;
    auto remove(K key) -> void override;
    auto parent() const noexcept -> weak_ptr<Node> override;

    LeafNode(shared_ptr<R> &&record, K key, weak_ptr<Node> parent = nullptr);
    ~LeafNode() override;

  private:
    array<shared_ptr<R>, M> mRecordPointers;
    array<K, M> mKeys;
    weak_ptr<Node> mParent;
    shared_ptr<LeafNode> mSibling;
  };

  /*
  NonLeafNode
  */
  template <class K, class R, size_t M>
  class NonLeafNode : public BPTree<K, R, M>::AbstNode
  {
  public:
    using Node = typename BPTree<K, R, M>::AbstNode;

    auto keys() const noexcept -> const array<K, M> & override;
    auto insert(shared_ptr<R> &&record, K key) -> void override;
    auto remove(K key) -> void override;
    auto parent() const noexcept -> weak_ptr<Node> override;

    NonLeafNode(shared_ptr<R> &&record, K key, weak_ptr<Node> parent = nullptr);
    ~NonLeafNode() override;

  private:
    array<shared_ptr<Node>, M + 1> mChildren;
    array<K, M> mKeys;
    weak_ptr<Node> mParent;
  };

}; // namespace bptree

#include "bptree.tpp"
#include "bp_leaf_node.tpp"
#include "bp_nonleaf_node.tpp"

#endif // BPTREE_BPTREE
