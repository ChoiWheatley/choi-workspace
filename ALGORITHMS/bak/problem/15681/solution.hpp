#include <array>
#include <vector>

using std::array;
using std::vector;
using usize = unsigned long long;
using isize = long long;
using Idx = isize;
using Cnt = usize;

constexpr usize N = 100000;
constexpr usize Q = 100000;

struct PtrNode {
  vector<PtrNode *> children;
  PtrNode *parent;
  explicit PtrNode() = default;
  auto add_child(PtrNode *child) { this->children.push_back(child); }
  auto count_subtree() const -> Cnt {
    Cnt sum = 0;
    for (auto const *child : children) {
      sum += child->count_subtree();
    }
    return sum + 1;
  }
};

static PtrNode g_mem_pool[N + 1];
inline PtrNode *g_node_at(Idx index) {
  PtrNode *ret = g_mem_pool + index;
  return ret;
}

struct IdxNode {
  Idx id = -1;
  Idx next_sibling = -1;
};

/// flatten 1d linked list array
struct LinkedList {
  vector<IdxNode> nodes;
  array<Idx, 2 * N + 2> heads;
};

class Tree {

public:
  auto count_subtree_of(Idx root) const -> Cnt {
    return g_node_at(root)->count_subtree();
  }
};

class TreeBuilder {
  LinkedList ls;

  /// add children EXCEPT its parent node
  auto dfs(Idx cur, Idx parent) const -> void {
    PtrNode *cur_p = g_node_at(cur);
    cur_p->parent = g_node_at(parent);
    Idx child = ls.heads[cur];
    while (child != -1) {
      IdxNode node = ls.nodes[child];
      child = node.next_sibling;

      if (node.id == parent) {
        continue;
      }
      // node is child of `cur`
      cur_p->add_child(g_node_at(node.id));
      // do dfs
      this->dfs(node.id, cur);
    }
  }

public:
  explicit TreeBuilder() {
    // index starts with 1
    ls.nodes.emplace_back();
    ls.heads.fill(-1);
  }
  /// not yet know about who is the parent node
  /// so we will just push bi-directionaly
  auto add_connection(Idx a, Idx b) {
    // a -> b
    IdxNode new_node = {.id = a, .next_sibling = ls.heads[b]};
    ls.nodes.emplace_back(std::move(new_node));
    ls.heads[b] = ls.nodes.size() - 1;

    // b -> a
    new_node = {.id = b, .next_sibling = ls.heads[a]};
    ls.nodes.emplace_back(std::move(new_node));
    ls.heads[a] = ls.nodes.size() - 1;
  }

  /// use dfs style tree structuring
  auto build(Idx root) const -> Tree {
    PtrNode *root_p = g_node_at(root);
    root_p->parent = nullptr;

    Idx child = ls.heads[root];
    while (child != -1) {
      IdxNode node = ls.nodes[child];
      child = node.next_sibling;

      root_p->add_child(g_node_at(node.id));
      // do dfs for all children
      this->dfs(node.id, root);
    }

    // Tree instance is just marker for safely usable for `Node`s
    return Tree();
  }
};