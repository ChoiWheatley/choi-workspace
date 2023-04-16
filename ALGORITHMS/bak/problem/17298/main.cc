#include <cassert>
#include <cstddef>
#include <ios>
#include <iostream>
#include <iterator>
#include <limits>
#include <stack>
#include <vector>

#define cr const &

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  int max = std::numeric_limits<int>::min();
  vector<int> nge(n);
  vector<int> inputs(n);
  stack<int> candidates;

  for (int i = 0; i < n; ++i) {
    cin >> inputs[i];
  }

  for (int i = n - 1; i >= 0; --i) {
    if (max <= inputs[i]) {
      max = inputs[i];
      candidates.push(inputs[i]);
      nge[i] = -1;
      continue;
    }
    while (true) {
      if (candidates.empty()) {
        // corner case
        nge[i] = -1;
        break;
      }
      if (inputs[i] < candidates.top()) {
        nge[i] = candidates.top();
        candidates.push(inputs[i]);
        break;
      }
      candidates.pop();
    }
  }

  for (auto cr e : nge) {
    cout << e << " ";
  }
  cout << "\n";

  return 0;
}