#include <memory>
#include <array>
#include <optional>
#include <string>

namespace bptree
{
  using std::array;
  using std::optional;
  using std::shared_ptr;

  template <class Key, class Record, size_t M>
  inline auto isLeaf(BPTree<Key, Record, M> *node) -> bool
  {
    return (
        dynamic_cast<LeafNode<Key, Record, M> *>(node));
  }

  template <class Key, class Record, size_t M>
  BPTree<Key, Record, M>::BPTree() : mRoot{nullptr} {}

  template <class Key, class Record, size_t M>
  auto BPTree<Key, Record, M>::insert(shared_ptr<Record> record, Key key)
  {
    if (mRoot == nullptr)
    {
      mRoot = std::make_shared<LeafNode<Key, Record, M>>(std::move(record), key, mRoot);
      return;
    }
    if (mRoot->full() && isLeaf(mRoot.get()))
    // 루트노드가 리프이면서 동시에 가득찬 경우
    {
    }
    mRoot->insert(std::move(record), key);
    mSizeCache++;
  }

  template <class Key, class Record, size_t M>
  auto BPTree<Key, Record, M>::remove(Key key)
  {
    if (mRoot == nullptr)
    {
      return;
    }
    // TODO: 순회 및 정확한 key에 대응하는 노드를 찾아 삭제 및 재정렬.
    mSizeCache--;
  }

  template <class Key, class Record, size_t M>
  auto BPTree<Key, Record, M>::query(Key key) const noexcept -> optional<Record>
  {
    if (mRoot == nullptr)
    {
      return std::nullopt;
    }
    // TODO: 순회 및 key 찾기
  }

  template <class Key, class Record, size_t M>
  auto BPTree<Key, Record, M>::size() const noexcept -> size_t { return mSizeCache; }

}; // namespace bptree