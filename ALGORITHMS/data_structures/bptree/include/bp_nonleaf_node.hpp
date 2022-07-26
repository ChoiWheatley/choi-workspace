#ifndef BP_NONLEAF_NODE
#define BP_NONLEAF_NODE

#include <memory>
#include <array>
#include "bp_abstract_node.hpp"

namespace bptree
{
  /// Composite 패턴 중 Composite에 해당한다.
  /// case Root Node )
  ///   number of children = [2, b], b는 children의 수, 즉 KeyCount+1
  /// case Internal Node )
  ///   number of children = [ceil(b/2), b]
  template <typename KeyType, class RecordType, size_t KeyCount>
  class BPNonLeafNode
      : public BPTree<KeyType, RecordType, KeyCount>::BPAbstractNode
  {
    using AbstractNode = typename bptree::BPTree<KeyType, RecordType, KeyCount>::BPAbstractNode;

  public:
    auto keys() const -> const std::array<KeyType, KeyCount> & override;
    auto insert(unique_ptr<RecordType> record) -> void override;
    auto remove(const KeyType &key) -> unique_ptr<RecordType> override;
    auto query(const KeyType &key) const -> optional<RecordType> override;

    BPNonLeafNode();
    BPNonLeafNode(const BPNonLeafNode &) = delete;
    BPNonLeafNode &operator=(const BPNonLeafNode &) = delete;
    BPNonLeafNode(BPNonLeafNode &&) = delete;
    BPNonLeafNode &operator=(BPNonLeafNode &&) = delete;
    ~BPNonLeafNode() override;

  private:
    std::array<KeyType, KeyCount> m_keys;
    std::array<unique_ptr<AbstractNode>, KeyCount + 1> m_children;
  };

  template <typename KeyType, class RecordType, size_t KeyCount>
  BPNonLeafNode<KeyType, RecordType, KeyCount>::BPNonLeafNode()
  {
  }

  template <typename KeyType, class RecordType, size_t KeyCount>
  auto BPNonLeafNode<KeyType, RecordType, KeyCount>::keys() const -> const std::array<KeyType, KeyCount> &
  {
  }

  template <typename KeyType, class RecordType, size_t KeyCount>
  auto BPNonLeafNode<KeyType, RecordType, KeyCount>::insert(unique_ptr<RecordType> record) -> void
  {
  }

  template <typename KeyType, class RecordType, size_t KeyCount>
  auto BPNonLeafNode<KeyType, RecordType, KeyCount>::remove(const KeyType &key) -> unique_ptr<RecordType>
  {
  }

  template <typename KeyType, class RecordType, size_t KeyCount>
  auto BPNonLeafNode<KeyType, RecordType, KeyCount>::query(const KeyType &key) const -> optional<RecordType>
  {
  }
}

#endif // BP_NONLEAF_NODE