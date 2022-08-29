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

  /* helper functions related to Node */

  /// split (child nodes and keys) OR (records)
  template <class Key>
  auto split(const Node<Key> &node) -> std::pair<Node<Key>, Node<Key>>
  {
    switch (node.has)
    {
    case Has::ChildNodes:
    {
      const auto keySplitted = split(node.keys);
      const auto childSplitted = split(node.childNodes);
      Node<Key> first{Has::ChildNodes};
      Node<Key> second{Has::ChildNodes};
      first.keys = keySplitted.first;
      first.childNodes = childSplitted.first;
      second.keys = keySplitted.second;
      second.childNodes = childSplitted.second;

      return std::make_pair(first, second);
    }

    case Has::RecordPointers:
      const auto recordSplitted = split(node.records);
      Node<Key> first{Has::RecordPointers};
      Node<Key> second{Has::RecordPointers};
      first.records = recordSplitted.first;
      second.records = recordSplitted.second;

      return std::make_pair(first, second);
    }
  }

} // namespace bptree

#endif // NODE