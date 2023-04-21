#include <algorithm>
#include <array>
#include <bitset>
#include <cstddef>
#include <vector>

#define cr const &

// constexpr size_t N = 1000;
// constexpr size_t K = 100'000;
constexpr size_t N = 10;
constexpr size_t K = 10;

using std::array;
using std::bitset;
using std::for_each;
using std::vector;
using Vec = vector<int>;
using BitSet = bitset<N + 1>;

struct PtrNode {
  int id = -1;
  int next = -1;
};

/**
A -> B
B depends on A
A is depended on by B
A is the dependee
B is the depender
*/
struct Dependency {
  int dependee = -1;
  int depender = -1;
};

/**head of linked list*/
static array<int, N + 1> head;
/**fixed sized, flatten 1D array of linked lists*/
static array<PtrNode, K + 1> nodes;

static void init_linked_list(vector<Dependency> cr dependencies) {
  head.fill(-1);
  for (int i = 0; i < static_cast<int>(dependencies.size()); ++i) {
    auto cr dependee = dependencies[i].dependee;
    auto cr depender = dependencies[i].depender;
    nodes[i].id = depender;
    nodes[i].next = head[dependee];
    head[dependee] = i;
  }
}

/**
@brief: do a recursive topological sort.

@notice: https://www.geeksforgeeks.org/topological-sorting/
*/
static void topological_sort(int head_id, BitSet &visited, vector<int> &out) {

  auto node_ptr = head[head_id];
  while (node_ptr != -1) {
    // iterate adjacent nodes
    auto node = nodes[node_ptr];
    if (!visited[node.id]) {
      visited.set(node.id);
      // do prerequired node first!
      topological_sort(node.id, visited, out);
    }
    node_ptr = node.next;
  }
  // finally, we can safely push current node to the stack because no other
  // nodes prerequires this node.
  visited.set(head_id);
  out.push_back(head_id);
}

/**
@params:
- dependencies: directed edge that contains A -> B, where A is dependee, B is
depender

- weights: counted from zero(DISCLAIMER: the problem counts elements from one)
to N
*/
static int solution(vector<Dependency> &&dependencies, vector<int> &&weights,
                    int w) {

  init_linked_list(dependencies);

  BitSet visited;
  vector<int> sorted_rev;
  for (int i = 0; i < int(weights.size()); ++i) {
    if (!visited[i]) {
      topological_sort(i, visited, sorted_rev);
    }
  }

  auto results = vector<int>(weights);
  // Propagate weights into connected nodes.
  // In this problem, we have to choose bigger weights compare to merging from
  // different nodes.
  for_each(sorted_rev.crbegin(), sorted_rev.crend(), [&](auto cr from) {
    // for each node connected from `from` node
    auto node_ptr = head[from];
    while (node_ptr != -1) {
      auto node = nodes[node_ptr];

      results[node.id] =
          std::max(results[node.id],                // previously propagated one
                   weights[node.id] + results[from] // and newcomer `from`
          );

      node_ptr = node.next;
    }
  });

  return results[w];
}