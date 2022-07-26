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
    // template <typename KeyType_, class RecordType_>
    class BPAbstractNode;

  private:
    // using BPNode_ = BPTree::BPNode<KeyType, RecordType>;
    unique_ptr<BPAbstractNode> m_root;
  };

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

} // namespace bptree
