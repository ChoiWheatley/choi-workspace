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
using std::vector;
using Vec = vector<int>;
using BitSet = bitset<N + 1>;

struct Node {
  int id;
  int next;
};

/**
A -> B
B depends on A
A is depended on by B
A is the dependee
B is the depender
*/
struct Dependency {
  int dependee = 0;
  int depender = 0;
};

/**head of linked list*/
static array<int, N + 1> head;
/**fixed sized, flatten 1D array of linked lists*/
static array<Node, K + 1> nodes;

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

static int solution(vector<Dependency> &&dependencies, vector<int> &&weights,
                    int w) {

  init_linked_list(dependencies);

  BitSet visited;
  vector<int> sorted_rev;
  for (int i = 1; i <= int(dependencies.size()); ++i) {
    topological_sort(i, visited, sorted_rev);
  }

  return weights[w];
}