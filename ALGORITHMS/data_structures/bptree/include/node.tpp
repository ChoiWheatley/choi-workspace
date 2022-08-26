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

  /// Node can hold child nodes OR records
  template <class Key>
  struct Node
  {
    using _Record = Record<Key>;

    const Has has;                       // Both
    vector<Key> keys;                    // Has::ChildNodes
    vector<shared_ptr<Node>> childNodes; // Has::ChildNodes
    vector<shared_ptr<_Record>> records; // Has::RecordPointers
    shared_ptr<Node> sibling;            // Has::RecordPointers

    Node(Has has) : has{has} {};
    Node(const Node &other)
        : has{other.has}, keys{other.keys}, childNodes{other.childNodes},
          records{other.records}, sibling{other.sibling} {}
    ~Node(){};

    /// copy EXCEPT `has`
    auto operator=(const Node &other)
    {
      keys = other.keys;
      childNodes = other.childNodes;
      records = other.records;
      sibling = other.sibling;
      return *this;
    }
  };

} // namespace bptree

#endif // NODE