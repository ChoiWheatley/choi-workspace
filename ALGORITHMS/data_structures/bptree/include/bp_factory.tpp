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
  using std::shared_ptr;
  using std::unique_ptr;
  using std::vector;
  using std::weak_ptr;

  using index_t = size_t;

  template <class K, class R, size_t M>
  auto BPFactory<K, R, M>::
      childContainer() -> ChildContainable<K, R, M> &
  {
    return mChildContainer;
  }

  template <class K, class R, size_t M>
  auto BPFactory<K, R, M>::
      leafNode(weak_ptr<Node> parent,
               shared_ptr<Leaf> sibling) -> shared_ptr<Node>
  {
    return std::make_shared<Leaf>(parent, sibling);
  }

  template <class K, class R, size_t M>
  auto BPFactory<K, R, M>::
      nonLeafNode(weak_ptr<Node> parent) -> shared_ptr<Node>
  {
    return std::make_shared<NonLeaf>(
        ChildContainer<K, R, M>{},
        parent);
  }

  template <class K, class R, size_t M>
  BPFactory<K, R, M>::BPFactory()
      : mChildContainer{} {}

} // namespace bptree