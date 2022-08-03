#include "bp_helpers.hpp"
#include "bp_error.hpp"
#include <memory>
#include <array>
#include <optional>
#include <vector>
#include <utility>

namespace bptree
{
  using std::array;
  using std::shared_ptr;
  using std::unique_ptr;
  using std::vector;
  using std::weak_ptr;

  using index_t = size_t;

  /*
  ChildContainer
    NonLeafNode의 책임을 덜어주기 위해 나온 객체이다.
  */
  template <class K, class R, size_t M>
  class ChildContainer : public bptree::ChildContainable<K, R, M>
  {
  public:
    using Node = typename bptree::AbstNode<K, R, M>;
    using NodePtr = shared_ptr<Node>;

    auto childNodes() const noexcept -> const vector<NodePtr> & override {}
    auto childCount() const noexcept -> size_t override
    {
      // TODO: implement
      return 0;
    }
    auto attach(NodePtr child) -> void override {}
    auto detachChildBy(index_t idx) -> NodePtr override {}
    auto swapChild(NodePtr with) noexcept -> void override {}
  };

} // namespace bptree