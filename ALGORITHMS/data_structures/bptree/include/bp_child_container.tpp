#include "bp_error.hpp"
#include "bp_helpers.hpp"
#include <array>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

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

    auto childNodes() const noexcept -> const vector<NodePtr> & override
    {
      return mChildNodes;
    }

    auto childCount() const noexcept -> size_t override
    {
      return mChildNodes.size();
    }

    auto attach(NodePtr child, const vector<K> &fromKey) -> void override
    {
      if (full())
      {
        throw bptree::child_overflow{};
      }
      if (fromKey.empty())
      {
        // no way to attach, throw.
        throw bptree::child_out_of_range{};
      }
        }

    auto detachChildBy(index_t idx) -> NodePtr override {}

    auto swapChild(NodePtr with) noexcept -> void override {}

    auto full() const noexcept -> bool override
    {
      return (childCount() >= M + 1);
    }

    auto empty() const noexcept -> bool override
    {
      return (childCount() == 0);
    }

  private:
    auto doAttach(NodePtr child, index_t idx) -> void {}

    vector<NodePtr> mChildNodes;
    vector<index_t> mLookupTable;
  };

} // namespace bptree