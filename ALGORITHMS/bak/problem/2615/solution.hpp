#ifndef SOLUTION
#define SOLUTION

#include <array>
#include <cstring>
using namespace std;

constexpr int MAX_SIDE = 19;

constexpr array<array<int, 2>, 4> DELTAS = {{
    {-1, 0},
    {-1, 1},
    {0, 1},
    {1, 1},
}};

constexpr bool is_inside(int i, int j) {
  return 0 <= i && i < MAX_SIDE && 0 <= j && j < MAX_SIDE;
}

enum class Stone { Blank = 0, Black = 1, White = 2 };

struct Return {
  Stone stone;
  int row;
  int col;
};

Return solution(Stone game[MAX_SIDE][MAX_SIDE]) {
  for (int i = 0; i < MAX_SIDE; ++i) {
    for (int j = 0; j < MAX_SIDE; ++j) {
      auto stone = game[i][j];
      if (stone == Stone::Blank) {
        continue;
      }
      // check for 8 directions
      for (auto delta_each : DELTAS) {
        const int delta_i = delta_each[0];
        const int delta_j = delta_each[1];
        int straight_count = 1;
        int new_i = i + delta_i;
        int new_j = j + delta_j;

        while (is_inside(new_i, new_j) && game[new_i][new_j] == stone) {
          straight_count += 1;
          new_i += delta_i;
          new_j += delta_j;
        }

        new_i = i - delta_i;
        new_j = j - delta_j;

        while (is_inside(new_i, new_j) && game[new_i][new_j] == stone) {
          straight_count += 1;
          new_i -= delta_i;
          new_j -= delta_j;
        }

        if (straight_count == 5) {
          if (new_j < j) {
            return Return{stone, new_i + delta_i, new_j + delta_j};
          }
          return Return{stone, i, j};
        }
      }
    }
  }
  return Return{Stone::Blank, 0, 0};
}

#endif