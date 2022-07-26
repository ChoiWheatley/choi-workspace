#ifndef BPTREE_BPTREE
#define BPTREE_BPTREE

#include <memory>
#include <optional>
#include <array>

namespace bptree
{
  using std::optional;
  using std::unique_ptr;

  /// BPTree는 Client로부터 인터페이스를 주고받는 facade이다.
  /// Forwarded declaration
  template <typename KeyType, class RecordType, size_t KeyCount = 4>
  class BPTree
  {
  public:
    auto insert(unique_ptr<RecordType> record) -> void;
    auto remove(const KeyType &key) -> unique_ptr<RecordType>;
    auto query(const KeyType &key) const -> RecordType;

    BPTree() = default;

  protected:
    class BPAbstractNode;

  private:
    unique_ptr<BPAbstractNode> m_root;
  };

  template <typename KeyType, class RecordType, size_t KeyCount>
  auto BPTree<KeyType, RecordType, KeyCount>::insert(unique_ptr<RecordType> record) -> void
  {
  }

  template <typename KeyType, class RecordType, size_t KeyCount>
  auto BPTree<KeyType, RecordType, KeyCount>::remove(const KeyType &key) -> unique_ptr<RecordType>
  {
  }

  template <typename KeyType, class RecordType, size_t KeyCount>
  auto BPTree<KeyType, RecordType, KeyCount>::query(const KeyType &key) const -> RecordType
  {
  }

} // namespace bptree

#endif // BPTREE_BPTREE