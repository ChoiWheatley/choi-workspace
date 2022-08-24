#include <memory>
#include <vector>

namespace bptree
{
  using std::shared_ptr;
  using std::unique_ptr;
  using std::vector;

  template <class Key>
  struct NodeImpl : public Node<Key>
  {
    using R = Record<Key>;
    using N_p = shared_ptr<Node<Key>>;
    using R_p = shared_ptr<R>;
    auto has() const -> Has override
    {
      return has_;
    }

    auto childNodes() -> vector<N_p> & override
    {
      return childNodes_;
    }

    auto records() -> vector<R_p> & override
    {
      return records_;
    }

    NodeImpl(Has has)
        : Node<Key>(), has_{has} {};
    ~NodeImpl(){};

  private:
    // resolved at constructor-time
    const Has has_;

    vector<N_p> childNodes_;
    vector<R_p> records_;
  }; // struct NodeImpl
} // namespace bptree