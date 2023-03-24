#include "solution.hpp"
#include <ios>
#include <iostream>

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int k;
  int sides[6];
  int directions[6];

  cin >> k;

  for (int i = 0; i < 6; ++i) {
    cin >> directions[i] >> sides[i];
  }

  int submit = solution(sides, directions, k);

  cout << submit << "\n";

  return 0;
}