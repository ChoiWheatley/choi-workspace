#include "solution.hpp"
#include <ios>
#include <iostream>

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  usize n, r, q;
  cin >> n >> r >> q;

  auto builder = TreeBuilder();
  for (usize i = 0; i < n - 1; ++i) {
    Idx u, v;
    cin >> u >> v;
    builder.add_connection(u, v);
  }

  auto tree = builder.build(r);

  for (usize i = 0; i < q; ++i) {
    Idx query_idx;
    cin >> query_idx;
    cout << tree.count_subtree_of(query_idx) << "\n";
  }

  return 0;
}