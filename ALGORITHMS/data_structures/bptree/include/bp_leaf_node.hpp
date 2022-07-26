#ifndef BP_LEAF_NODE
#define BP_LEAF_NODE

#include "bp_abstract_node.hpp"

namespace bptree
{
  /// Composite 패턴 중 leaf에 해당한다.
  /// B+tree 에서 leaf는 실제 레코드에 참조하는 포인터가 있다.
  template <typename KeyType, class RecordType, size_t KeyCount>
  class BPLeafNode
      : public BPTree<KeyType, RecordType, KeyCount>::BPAbstractNode
  {
  public:
    auto keys() const -> const std::array<KeyType, KeyCount> & override;
    auto insert(unique_ptr<RecordType> record) -> void override;
    auto remove(const KeyType &key) -> unique_ptr<RecordType> override;
    auto query(const KeyType &key) const -> optional<RecordType> override;

    BPLeafNode();
    BPLeafNode(const BPLeafNode &) = delete;
    BPLeafNode &operator=(const BPLeafNode &) = delete;
    BPLeafNode(BPLeafNode &&) = delete;
    BPLeafNode &operator=(BPLeafNode &&) = delete;
    ~BPLeafNode() override;

  private:
    std::array<KeyType, KeyCount> m_keys;
    std::array<unique_ptr<RecordType>, KeyCount> m_recordPointers;
  };

  template <typename KeyType, class RecordType, size_t KeyCount>
  BPLeafNode<KeyType, RecordType, KeyCount>::BPLeafNode()
  {
  }

  template <typename KeyType, class RecordType, size_t KeyCount>
  auto BPLeafNode<KeyType, RecordType, KeyCount>::keys() const -> const std::array<KeyType, KeyCount> &
  {
  }

  template <typename KeyType, class RecordType, size_t KeyCount>
  auto BPLeafNode<KeyType, RecordType, KeyCount>::insert(unique_ptr<RecordType> record) -> void
  {
  }

  template <typename KeyType, class RecordType, size_t KeyCount>
  auto BPLeafNode<KeyType, RecordType, KeyCount>::remove(const KeyType &key) -> unique_ptr<RecordType>
  {
  }

  template <typename KeyType, class RecordType, size_t KeyCount>
  auto BPLeafNode<KeyType, RecordType, KeyCount>::query(const KeyType &key) const -> optional<RecordType>
  {
  }

}

#endif // BP_LEAF_NODE