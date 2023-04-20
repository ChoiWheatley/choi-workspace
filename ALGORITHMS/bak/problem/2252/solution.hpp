#include <algorithm>
#include <array>
#include <queue>
#include <vector>

using std::array;
using std::queue;
using std::vector;

using Idx = int;
using Elm = int;
using Cnt = int;

#define cr const &

constexpr Cnt N = 32'000;
constexpr Cnt M = 100'000;

using VecInDegree = vector<Cnt>;
using Queue = queue<Idx>;

class Builder;
struct Node {
  Idx idx = -1;
  Idx next_sibling = -1;
};
struct LinkedList {
  array<Idx, N + 1> heads;
  vector<Node> nodes;
};

class TopoSort {

  Cnt edge_cnt;
  Cnt vertex_cnt;
  LinkedList ls;
  VecInDegree in_degree;
  Queue cached_queue;

  explicit TopoSort(LinkedList &&ls, VecInDegree &&in_degree, Cnt edge_cnt,
                    Cnt vertex_cnt)
      : edge_cnt(edge_cnt), vertex_cnt(vertex_cnt), ls(std::move(ls)),
        in_degree(std::move(in_degree)) {}

  friend class Builder;

public:
  class cycle_has_detected_error {};

  /**
  @brief: do topological sort, throws when cycles has detected
  */
  auto sort() -> Queue cr {
    if (!cached_queue.empty()) {
      return cached_queue;
    }

    // push all nodes which has zero in-degrees
    Queue tmp_queue;
    // count from 1
    for (Idx i = 1; i <= vertex_cnt; ++i) {
      if (in_degree[i] == 0) {
        tmp_queue.push(i);
      }
    }

    while (!tmp_queue.empty()) {
      Idx idx = tmp_queue.front();
      cached_queue.push(idx);
      tmp_queue.pop();

      // update in-degrees connected from this node
      Idx sibling = ls.heads[idx];
      while (sibling != -1) {
        Node node = ls.nodes[sibling];
        in_degree[node.idx] -= 1;
        if (in_degree[node.idx] == 0) {
          // newly founded zero-in-degree node
          tmp_queue.push(node.idx);
        }
        sibling = node.next_sibling;
      }
    }

    // check this graph has cycles
    for (auto cnt : in_degree) {
      if (cnt > 0) {
        // @@@@@ CYCLE DETECTED!!!!!
        throw cycle_has_detected_error{};
      }
    }

    return cached_queue;
  }
};

class Builder {
  Cnt vertex_cnt;
  Cnt edge_cnt;
  LinkedList ls;
  VecInDegree in_degree;

public:
  /**
  @brief: add new edge into flatten 1d-linked-list, updating `in_degree`
  either
  */
  auto add_edge(Idx from, Idx to) -> void {
    in_degree[to] += 1;
    ls.nodes.push_back(Node{.idx = to, .next_sibling = ls.heads[from]});
    ls.heads[from] = int(ls.nodes.size() - 1);
  }
  auto build() -> TopoSort {
    return TopoSort(std::move(ls), std::move(in_degree), edge_cnt, vertex_cnt);
  }
  explicit Builder(Cnt vertex_cnt, Cnt edge_cnt)
      : vertex_cnt(vertex_cnt), edge_cnt(edge_cnt), in_degree(vertex_cnt + 1) {
    ls.heads.fill(-1);
    // index counts from 1
    ls.nodes.push_back(Node());
  };
};