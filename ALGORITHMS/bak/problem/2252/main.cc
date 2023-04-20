#include "solution.hpp"
#include <ios>
#include <iostream>

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  Cnt n, m;
  cin >> n >> m;

  auto builder = Builder(n, m);
  for (int i = 0; i < m; ++i) {
    Idx from, to;
    cin >> from >> to;
    builder.add_edge(from, to);
  }

  auto toposort = builder.build();

  Queue result = toposort.sort();

  while (!result.empty()) {
    Idx peek = result.front();
    result.pop();
    cout << peek << ' ';
  }
  cout << "\n";

  return 0;
}