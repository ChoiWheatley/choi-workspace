#include <array>
#include <cstddef>
#include <vector>

#define cr const &

constexpr size_t N = 1000;
constexpr size_t K = 100'000;
// constexpr size_t N = 10;
// constexpr size_t K = 10;

using std::array;
using std::vector;
using Vec = vector<int>;

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
static array<int, N> head;
/**fixed sized, flatten 1D array of linked lists*/
static array<Node, K> nodes;

static void init_linked_list(vector<Dependency> cr dependencies) {
  head.fill(-1);
  for (int i = 0; i < static_cast<int>(dependencies.size()); ++i) {
    auto cr dependee = dependencies[i].dependee;
    auto cr depender = dependencies[i].depender;
    nodes[i].id = dependee;
    nodes[i].next = head[depender];
    head[depender] = i;
  }
}

/**
@brief: Do **DFS** to find the max time until independent node has found

might time-out because naive DFS is O(N * N)
*/
static int solution_recur(vector<int> cr weights, int node_id) {
  if (head[node_id] == -1) {
    // exit condition
    return weights[node_id];
  }
  int next_ptr = head[node_id];
  int max_weight = 0;
  while (next_ptr != -1) {
    max_weight =
        std::max(max_weight, solution_recur(weights, nodes[next_ptr].id));
    next_ptr = nodes[next_ptr].next;
  }
  return max_weight + weights[node_id];
}

static int solution(vector<Dependency> &&dependencies, vector<int> &&weights,
                    int w) {
  // normalize
  for (auto &e : dependencies) {
    e.dependee -= 1;
    e.depender -= 1;
  }
  // normalize
  w -= 1;
  init_linked_list(dependencies);
  return solution_recur(weights, w);
}