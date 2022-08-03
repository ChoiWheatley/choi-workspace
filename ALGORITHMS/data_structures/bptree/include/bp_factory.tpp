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

  /*
  BPFactory
  */
  template <class K, class R, size_t M>
  class BPFactory
  {
  public:
    using Node = typename bptree::AbstNode<K, R, M>;
    using Leaf = typename bptree::LeafNode<K, R, M>;
    using NonLeaf = typename bptree::NonLeafNode<K, R, M>;
    using ChildContainer_ = typename bptree::ChildContainer<K, R, M>;
    using NodePtr = shared_ptr<Node>;
    using LeafPtr = shared_ptr<Leaf>;
    using NonLeafPtr = shared_ptr<NonLeaf>;
    using ChildContainerPtr = shared_ptr<ChildContainer_>;

    auto childContainer() -> ChildContainerPtr;
    auto leafNode(weak_ptr<Node> parent = weak_ptr<Node>{},
                  shared_ptr<Leaf> sibling = shared_ptr<Leaf>{}) -> LeafPtr;
    auto nonLeafNode(weak_ptr<Node> parent = weak_ptr<Node>{}) -> NonLeafPtr;
  };

  template <class K, class R, size_t M>
  auto BPFactory<K, R, M>::
      childContainer() -> ChildContainerPtr
  {
    return std::make_shared<ChildContainer_>();
  }

  template <class K, class R, size_t M>
  auto BPFactory<K, R, M>::
      leafNode(weak_ptr<Node> parent,
               shared_ptr<Leaf> sibling) -> LeafPtr
  {
    return std::make_shared<Leaf>(parent, sibling);
  }

  template <class K, class R, size_t M>
  auto BPFactory<K, R, M>::
      nonLeafNode(weak_ptr<Node> parent) -> NonLeafPtr
  {
    return std::make_shared<NonLeaf>(
        std::make_shared<ChildContainer_>(),
        parent);
  }

} // namespace bptree