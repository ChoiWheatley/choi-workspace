#ifndef BP_APBSTRACT_NODE
#define BP_APBSTRACT_NODE

#include "bptree.hpp"

namespace bptree
{
  /// Composite 패턴 중 추상화 컴포넌트를 담당한다.
  /// leaf와 non-leaf에서 공통적인 특징을 추상화 한다.
  template <typename KeyType, class RecordType, size_t KeyCount>
  class BPTree<KeyType, RecordType, KeyCount>::BPAbstractNode
  {
    using AbstractNode = typename bptree::BPTree<KeyType, RecordType, KeyCount>::BPAbstractNode;

  public:
    virtual auto keys() const -> const std::array<KeyType, KeyCount> & = 0;
    virtual auto insert(unique_ptr<RecordType> record) -> void = 0;
    virtual auto remove(const KeyType &key) -> unique_ptr<RecordType> = 0;
    virtual auto query(const KeyType &key) const -> optional<RecordType> = 0;

    BPAbstractNode() = default;
    BPAbstractNode(const BPAbstractNode &copy) = delete;
    BPAbstractNode &operator=(const BPAbstractNode &copy) = delete;
    BPAbstractNode(BPAbstractNode &&move) = delete;
    BPAbstractNode &operator=(BPAbstractNode &&move) = delete;
    virtual ~BPAbstractNode() = default;
  };

} // namespace bptree

#endif // BP_APBSTRACT_NODE