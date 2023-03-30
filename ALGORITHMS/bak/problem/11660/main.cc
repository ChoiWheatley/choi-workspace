#include "solution.hpp"
#include <array>
#include <cstddef>
#include <ios>
#include <iostream>

using namespace std;

static Arr arr;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int side;
  int testcase;
  cin >> side >> testcase;

  for (int i = 0; i < side; ++i) {
    for (int j = 0; j < side; ++j) {
      int input;
      cin >> input;
      add_to(arr, i, j, side, side, input);
    }
  }

  // now arr is now cumulative sum!

  for (int t = 0; t < testcase; ++t) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    int submit = sum_between(arr, x1 - 1, y1 - 1, x2 - 1, y2 - 1, side, side);
    cout << submit << "\n";
  }

  return 0;
}