#ifndef BPTREE_BPTREE
#define BPTREE_BPTREE

#include "bp_error.hpp"
#include <memory>
#include <array>
#include <optional>
#include <vector>
#include <utility>

namespace bptree
{
  using std::array;
  using std::nullopt;
  using std::optional;
  using std::pair;
  using std::shared_ptr;
  using std::unique_ptr;
  using std::vector;
  using std::weak_ptr;

  using index_t = size_t;

  template <class K, class R, size_t M>
  class AbstNode;

  template <class K, class R, size_t M>
  class LeafNode;

  template <class K, class R, size_t M>
  class NonLeafNode;

  /// insert 시 발생한 오버플로를 ceil(M/2) 크기의 벡터로 쪼갠다.
  template <class Key, size_t M>
  auto unsaturate(const vector<Key> &saturated) noexcept -> vector<array<index_t, M>>;

  /// node가 LeafNode인지 확인한다.
  template <class Key, class Record, size_t M>
  inline auto isLeaf(AbstNode<Key, Record, M> *node) -> bool;

  /// key와 일치하거나 들어갈 수 있는 리프노드를 리턴한다.
  template <class Key, class Record, size_t M>
  auto tour(const Key &key, shared_ptr<AbstNode<Key, Record, M>> pRoot) -> const shared_ptr<LeafNode<Key, Record, M>>;

  /*
  BPTree
  */
  template <class Key, class Record, size_t M>
  class BPTree
  {
  public:
    using Node = typename bptree::AbstNode<Key, Record, M>;
    using Leaf = typename bptree::LeafNode<Key, Record, M>;
    using NonLeaf = typename bptree::NonLeafNode<Key, Record, M>;

    auto insert(shared_ptr<Record> record, Key key);
    auto remove(Key key);
    auto query(Key key) const noexcept -> optional<Record>;
    auto size() const noexcept -> size_t;
    auto depth() const noexcept -> size_t;
    // TODO: BPTree iterator 만들어보기
    // TODO: Bulk Loading 구현해보기

    BPTree();

  private:
    shared_ptr<Node> mRoot;
    size_t mSizeCache = 0;
  };

  /*
  AbstNode
  */
  template <class K, class R, size_t M>
  class AbstNode
  {
  public:
    virtual auto keys() const noexcept -> const array<optional<K>, M> & = 0;
    virtual auto insert(shared_ptr<R> record, K key) -> void = 0;
    virtual auto remove(K key) -> void = 0;
    virtual auto parent() const noexcept -> weak_ptr<AbstNode> = 0;
    virtual auto full() const noexcept -> bool = 0;
    virtual auto empty() const noexcept -> bool = 0;
    virtual auto keySize() const noexcept -> size_t = 0;
    virtual auto validate() const noexcept -> bool = 0;
    virtual ~AbstNode(){};
  };

  /*
  LeafNode
  */
  template <class K, class R, size_t M>
  class LeafNode : public AbstNode<K, R, M>
  {
  public:
    using Node = typename bptree::AbstNode<K, R, M>;
    using RecordPTR = shared_ptr<R>;
    auto keys() const noexcept -> const array<optional<K>, M> & override;
    auto insert(shared_ptr<R> record, K key) -> void override;
    auto remove(K key) -> void override;
    auto parent() const noexcept -> weak_ptr<Node> override;
    auto full() const noexcept -> bool override;
    auto empty() const noexcept -> bool override;
    auto keySize() const noexcept -> size_t override;
    auto validate() const noexcept -> bool override;

    auto recordPointers() const noexcept -> const array<RecordPTR, M> &;
    auto recordPointerSize() const noexcept -> size_t;

    explicit LeafNode(weak_ptr<Node> parent, shared_ptr<LeafNode> sibling);
    explicit LeafNode();
    LeafNode(LeafNode &&);
    LeafNode(const LeafNode &) = delete;
    ~LeafNode() override;

  private:
    array<optional<K>, M> mKeys;
    array<optional<RecordPTR>, M> mRecordPointers;
    weak_ptr<Node> mParent;
    shared_ptr<LeafNode> mSibling;

    auto doInsert(shared_ptr<R> record, K key, size_t idx);
    auto doRemove(K key, size_t idx);
  };

  /*
  NonLeafNode
  */
  template <class K, class R, size_t M>
  class NonLeafNode : public AbstNode<K, R, M>
  {
  public:
    using Node = typename bptree::AbstNode<K, R, M>;
    auto keys() const noexcept -> const array<optional<K>, M> & override;
    auto insert(shared_ptr<R> record, K key) -> void override;
    auto remove(K key) -> void override;
    auto parent() const noexcept -> weak_ptr<Node> override;
    auto full() const noexcept -> bool override;
    auto empty() const noexcept -> bool override;
    auto keySize() const noexcept -> size_t override;

    NonLeafNode(K key, weak_ptr<Node> parent = nullptr);
    ~NonLeafNode() override;

  private:
    array<shared_ptr<Node>, M + 1> mChildren;
    array<optional<K>, M> mKeys;
    weak_ptr<Node> mParent;
  };

}; // namespace bptree

#include "bptree.tpp"
#include "bp_leaf_node.tpp"
#include "bp_nonleaf_node.tpp"

#endif // BPTREE_BPTREE
