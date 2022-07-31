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
  inline auto isLeaf(AbstNode<Key, Record, M> *node) -> bool
  {
    return (
        dynamic_cast<LeafNode<Key, Record, M> *>(node));
  }

  template <class Key, class Record, size_t M>
  auto tour(const Key &key, shared_ptr<AbstNode<Key, Record, M>> pRoot) -> const shared_ptr<LeafNode<Key, Record, M>>
  {
  }

  template <class Key, class Record, size_t M>
  BPTree<Key, Record, M>::BPTree() : mRoot{nullptr} {}

  template <class Key, class Record, size_t M>
  auto BPTree<Key, Record, M>::insert(shared_ptr<Record> record, Key key)
  {
    if (mRoot.use_count() == 0)
    {
      mRoot = std::make_shared<LeafNode<Key, Record, M>>();
      mRoot->insert(record, key);
    }
    else
    {
      // TODO: 순회 후 cursor를 올바른 노드에 올려놓는다.
      shared_ptr<Leaf> cursor = tour<Key, Record, M>(key, mRoot);
      if (cursor->full())
      {
        // TODO: unsaturate()를 통해 노드를 쪼갠다.

        // TODO: findAscender()를 통해 sub-tree를 만든다.
        if (cursor.get() == mRoot.get())
        {
          // TODO: mRoot에 새 sub-tree를 연결한다.
          // TODO: mRoot의 자식을 연결한다.
        }
        // TODO: cursor의 부모에 sub-tree를 전파한다.
      }
      else
      {
        // TODO: 해당 커서에 key와 record를 추가한다.
        // cursor->insert(keyrecord);
      }
    }
    // finally : 내부 상태를 변화시키는 것은 맨 마지막에 수행한다.
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

  template <class Key, class Record, size_t M>
  auto BPTree<Key, Record, M>::depth() const noexcept -> size_t {}
}; // namespace bptree