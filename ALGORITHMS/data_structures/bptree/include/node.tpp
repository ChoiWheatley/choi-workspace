#ifndef NODE
#define NODE

#include "forward_decl.hpp"
#include <memory>
#include <vector>

namespace bptree
{
  using std::shared_ptr;
  using std::unique_ptr;
  using std::vector;

  // Node can hold child nodes OR records
  template <class Key>
  struct Node
  {
    using _Record = Record<Key>;
    // using N_p = shared_ptr<Node>;
    // using R_p = shared_ptr<R>;

    const Has has;
    Key key;
    vector<shared_ptr<Node>> childNodes;
    vector<shared_ptr<_Record>> records;
    shared_ptr<Node> sibling;

    auto childKeys() const -> const vector<Key>
    {
      vector<Key> ret{};
      for (const auto &k : childNodes)
      {
        ret.push_back(k->key);
      }
      return ret;
    }

    Node(Has has) : has{has} {};
    ~Node(){};
  };

} // namespace bptree

#endif // NODE