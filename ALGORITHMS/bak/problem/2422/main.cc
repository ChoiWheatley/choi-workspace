#include "solution.hpp"
#include <ios>
#include <iostream>

using std::cin;
using std::cout;
using std::ios;

ArrArr sparse_matrix;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  int m;
  cin >> n >> m;

  for (int i = 0; i < m; ++i) {
    int a;
    int b;
    cin >> a >> b;
    sparse_matrix[a][b] = true;
    sparse_matrix[b][a] = true;
  }

  auto submit = solution(sparse_matrix, n);

  cout << submit << "\n";

  return 0;
}