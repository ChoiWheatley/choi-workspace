#include <memory>
#include <array>
#include <optional>
#include <string>

namespace bptree
{
  template <class K, class R, size_t M>
  LeafNode<K, R, M>::LeafNode(shared_ptr<R> &&record, K key, weak_ptr<Node> parent)
      : mRecordPointers{array<shared_ptr<R>, M>()},
        mKeys{array<K, M>()},
        mParent{parent},
        mSibling{}
  {
    mRecordPointers.at(0) = record;
    mKeys.at(0) = key;
  }
} // namespace bptree