#include "solution.hpp"
#include <ios>
#include <iostream>

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  Idx height, width;
  cin >> height >> width;

  auto ub = UniverseBuilder(height, width);

  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      char read;
      cin >> read;
      if (read == '0') {
        ub.add_empty(i, j);
      }
    }
  }

  Cnt submit = solution(ub);
  cout << submit << "\n";

  return 0;
}