#include "solution.hpp"
#include <cstring>
#include <ios>
#include <iostream>
#include <istream>

using namespace std;

istream &operator>>(istream &is, Stone &stone) {
  int input;
  is >> input;
  stone = static_cast<Stone>(input);
  return is;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  Stone game[MAX_SIDE][MAX_SIDE];
  for (int i = 0; i < MAX_SIDE; ++i) {
    for (int j = 0; j < MAX_SIDE; ++j) {
      cin >> game[i][j];
    }
  }

  Return submit = solution(game);
  if (submit.stone == Stone::Blank) {
    cout << 0 << "\n";
  } else {
    cout << static_cast<int>(submit.stone) << "\n";
    cout << submit.row + 1 << " " << submit.col + 1 << "\n";
  }

  return 0;
}