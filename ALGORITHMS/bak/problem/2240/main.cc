#include "solution.hpp"
#include <ios>
#include <iostream>

using std::cin;
using std::cout;
using std::ios;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  int w;
  cin >> t >> w;

  vector<int> ls;
  while (t-- > 0) {
    int tree;
    cin >> tree;
    ls.push_back(tree == 1);
  }

  auto submit = solution(ls, w);

  cout << submit << "\n";

  return 0;
}