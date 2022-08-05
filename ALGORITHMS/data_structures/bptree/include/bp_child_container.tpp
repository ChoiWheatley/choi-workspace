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
  ChildContainable
    NonLeafNode가 childNodes를 회피하려는 책임을 명시하고 있는 인터페이스 목록이다.
  */
  template <class K, class R, size_t M>
  class ChildContainable
  {
  public:
    using Node = typename bptree::AbstNode<K, R, M>;
    using NodePtr = shared_ptr<Node>;
    virtual auto childNodes() const noexcept -> const vector<NodePtr> & = 0;
    virtual auto childCount() const noexcept -> size_t = 0;
    virtual auto attach(NodePtr child, const vector<K> &fromKey) -> void = 0;
    virtual auto detachChildBy(index_t idx) -> NodePtr = 0;
    virtual auto swapChild(NodePtr with) noexcept -> void = 0;
    virtual auto full() const noexcept -> bool = 0;
    virtual auto empty() const noexcept -> bool = 0;

    virtual ~ChildContainable(){};
  };

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
      // TODO: check cache is valid
      if (mChildNodesRearranged.empty())
      {
      }
      return mChildNodesRearranged;
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
      const vector<K> &childKeys = child->keys();
      const vector<K> &myKeys = fromKey;
      // [0]
      if (childKeys < myKeys[0])
      {
        mChildNodes.push_back(child);
        mLookupTable.push_back(0);
      }
      // [Last]
      else if (myKeys.back() <= childKeys)
      {
        mChildNodes.push_back(child);
        mLookupTable.push_back(myKeys.size());
      }
      // between [1] and [M-2]
      else
      {
        bool flag = false;
        for (size_t i = 1; i < myKeys.size() - 1; ++i)
        {
          if (myKeys[i - 1] <= childKeys && childKeys < myKeys[i])
          {
            mChildNodes.push_back(child);
            mLookupTable.push_back(i);
            flag = true;
          }
        }
        if (!flag)
        {
          throw bptree::child_out_of_range{};
        }
      }
      // reset cached output
      mChildNodesRearranged.clear();
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

    vector<NodePtr> mChildNodesRearranged{};
    vector<NodePtr> mChildNodes{};
    vector<index_t> mLookupTable{};
  };

} // namespace bptree