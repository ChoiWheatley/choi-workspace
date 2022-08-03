#ifndef BPTREE_BPTREE
#define BPTREE_BPTREE

#include "bp_error.hpp"
#include "bp_helpers.hpp"
#include <array>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

namespace bptree
{
  using std::array;
  using std::nullopt;
  using std::optional;
  using std::shared_ptr;
  using std::unique_ptr;
  using std::vector;
  using std::weak_ptr;

  using index_t = size_t;

  /*
  forward declarations
  */

  template <class K, class R, size_t M>
  class AbstNode;

  template <class K, class R, size_t M>
  class LeafNode;

  template <class K, class R, size_t M>
  class NonLeafNode;

  template <class K, class R, size_t M>
  class BPFactory;

  template <class K, class R, size_t M>
  class ChildContainable;

  template <class K, class R, size_t M>
  class ChildContainer;

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
    // TODO: array<optional<T>,M>을 vector<T>로 바꾸자.
    virtual auto keys() const noexcept -> const vector<K> & = 0;
    virtual auto keyCount() const noexcept -> size_t = 0;
    virtual auto parent() const noexcept -> weak_ptr<AbstNode> = 0;
    // TODO: parent setter가 필요함
    virtual auto full() const noexcept -> bool = 0;
    virtual auto empty() const noexcept -> bool = 0;
    virtual auto validate() const noexcept -> bool = 0;
    virtual ~AbstNode(){};
  };

  /*
  LeafNode
    중복을 허용하는 Key
  */
  template <class K, class R, size_t M>
  class LeafNode : public AbstNode<K, R, M>
  {
  public:
    using Node = typename bptree::AbstNode<K, R, M>;
    using RecordPtr = shared_ptr<R>;
    auto parent() const noexcept -> weak_ptr<Node> override;
    auto full() const noexcept -> bool override;
    auto empty() const noexcept -> bool override;
    auto validate() const noexcept -> bool override;
    auto keys() const noexcept -> const vector<K> & override;
    auto keyCount() const noexcept -> size_t override;

    // TODO: 파라메터 순서 Key, RecordPtr 순으로 변경하기
    auto insert(RecordPtr record, K key) -> void;
    auto records() const noexcept -> const vector<RecordPtr> &;
    auto recordCount() const noexcept -> size_t;
    auto remove(K key) -> void;
    auto sibling() -> shared_ptr<LeafNode>;
    auto attach(shared_ptr<LeafNode> sibling);
    auto detachSibling();

    explicit LeafNode(weak_ptr<Node> parent, shared_ptr<LeafNode> sibling);
    explicit LeafNode();
    LeafNode(LeafNode &&);
    LeafNode(const LeafNode &) = delete;
    ~LeafNode() override;

  private:
    vector<K> mKeys;
    vector<RecordPtr> mRecordPointers;
    weak_ptr<Node> mParent;
    shared_ptr<LeafNode> mSibling;

    auto doInsert(shared_ptr<R> record, K key, size_t idx);
    auto doRemove(size_t idx);
  };

  /*
  ChildContainable
    NonLeafNode가 childNodes를 회피하려는 책임을 명시하고 있는 인터페이스 목록이다.
  */
  template <class K, class R, size_t M>
  class ChildContainable
  {
  public:
    using Node = typename bptree::AbstNode<K, R, M>;
    using NodePtr = shared_ptr<Node>;
    virtual auto childNodes() const noexcept -> const vector<NodePtr> & = 0;
    virtual auto childCount() const noexcept -> size_t = 0;
    virtual auto attach(NodePtr child, const vector<K> &fromKey) -> void = 0;
    virtual auto detachChildBy(index_t idx) -> NodePtr = 0;
    virtual auto swapChild(NodePtr with) noexcept -> void = 0;
    virtual auto full() const noexcept -> bool = 0;
    virtual auto empty() const noexcept -> bool = 0;

    virtual ~ChildContainable(){};
  };

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
    auto childNodes() const noexcept -> const vector<NodePtr> &;
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

}; // namespace bptree

#include "bp_child_container.tpp"
#include "bp_factory.tpp"
#include "bp_leaf_node.tpp"
#include "bp_nonleaf_node.tpp"
#include "bptree.tpp"

#endif // BPTREE_BPTREE
