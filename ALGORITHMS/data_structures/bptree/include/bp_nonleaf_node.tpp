
#include <memory>
#include <array>
#include <optional>
#include <string>
#include <optional>

namespace bptree
{
  using std::array;
  using std::nullopt;
  using std::optional;
  using std::pair;
  using std::shared_ptr;
  using std::unique_ptr;
  using std::weak_ptr;

  template <class K, class R, size_t M>
  class AbstNode;

  template <class K, class R, size_t M>
  class LeafNode;

  template <class K, class R, size_t M>
  class NonLeafNode;

  // template <class K, class R, size_t M>
  // auto NonLeafNode::NonLeafNode(weak_ptr<Node> parent)
  //     : mChildren{}, mKeys{}, mParent{parent} {}

  // template <class K, class R, size_t M>
  // auto NonLeafNode::~NonLeafNode()
  // {
  //   delete mChildren;
  //   delete mKeys;
  //   mParent.reset();
  // }
} // namespace bptree