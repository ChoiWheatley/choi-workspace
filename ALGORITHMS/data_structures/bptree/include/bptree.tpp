#include <memory>
#include <vector>

namespace bptree
{
  template <class Key>
  class BPTreeImpl : public BPTree<Key>
  {
  public:
    using R = Record<Key>;
    using N = Node<Key>;

    auto Add(Key key, shared_ptr<R> record) -> void override
    {
      // TODO: impl
    }
    auto Delete(Key key) -> void override;
    auto Find(Key key) -> /*Nullable*/ R * override;

  private:
    unique_ptr<N> rootNode = nullptr;
  }; // class BPTreeImpl

} // namespace bptree
