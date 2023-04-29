#include <algorithm>
#include <array>
#include <bitset>
#include <iterator>
#include <queue>
#include <vector>
#define cr const &
using std::array;
using std::bitset;
using std::queue;
using std::vector;

using Idx = int;
using Cnt = int;
using State = bool;

struct Pos {
  Idx row;
  Idx col;
};
static inline Pos operator+(Pos cr lhs, Pos cr rhs) {
  return Pos{lhs.row + rhs.row, lhs.col + rhs.col};
}

constexpr Idx MAX_IDX = 1000;
constexpr array<Pos, 4> deltas = {
    Pos{-1, 0}, // up
    Pos{0, 1},  // right
    Pos{1, 0},  // down
    Pos{0, -1}, // left
};
using BitSet = bitset<MAX_IDX * MAX_IDX>;

class Universe {
  const Idx height;
  const Idx width;
  const BitSet region;

public:
  Universe(const Universe &) = default;
  Universe(Universe &&) = default;
  Universe &operator=(const Universe &) = delete;
  Universe &operator=(Universe &&) = delete;
  explicit Universe(BitSet &&region, Idx height, Idx width)
      : height(height), width(width), region(std::move(region)) {}

  /**
  @brief: can cope with off-the-range indexing, since this universe is
  donut-shaped, spliced with each upper side to down side, and each left side
  and right side.
  */
  auto get_index(Idx row, Idx col) const -> Idx {
    row %= this->height;
    col %= this->width;
    // `%` operator in C-family is not same as `mod` in math!!!! let's make it
    // same as `mod`
    if (row < 0) {
      row += this->height;
    }
    if (col < 0) {
      col += this->width;
    }
    return row * this->width + col;
  }

  auto get_index(Pos pos) const -> Idx {
    return this->get_index(pos.row, pos.col);
  }

  auto at(Idx row, Idx col) const -> State {
    return this->region[get_index(row, col)];
  }

  auto at(Pos pos) const -> State { return this->at(pos.row, pos.col); }
};

class UniverseBuilder {
  const Idx height;
  const Idx width;
  vector<Pos> empty_areas;

  auto get_index(Idx row, Idx col) const -> Idx {
    return row * this->width + col;
  }

public:
  explicit UniverseBuilder(Idx height, Idx width)
      : height(height), width(width) {}

  auto add_empty(Idx row, Idx col) {
    this->empty_areas.push_back(Pos{row, col});
  }

  auto build() const -> Universe {
    BitSet region;
    region.set();
    for (auto cr pos : empty_areas) {
      region.reset(get_index(pos.row, pos.col));
    }
    return Universe(std::move(region), this->height, this->width);
  }

  auto get_empty_areas() const -> vector<Pos> cr { return empty_areas; }
};

/**
@brief: using bfs to search empty regions in donut-shaped universe.
*/
inline static Cnt solution(UniverseBuilder cr ub) {
  BitSet visited;
  queue<Pos> q;

  auto univ = ub.build();
  Cnt cnt = 0;

  for (auto cr e : ub.get_empty_areas()) {
    if (visited[univ.get_index(e)]) {
      continue;
    }
    q.push(e);
    while (!q.empty()) {
      auto pos = q.front();
      q.pop();
      if (visited[univ.get_index(pos)]) {
        continue;
      }
      visited.set(univ.get_index(pos));

      for (auto cr delta : deltas) {
        auto next_pos = pos + delta;
        if (!univ.at(next_pos)) {
          // if this area is empty
          q.push(next_pos);
        }
      }
    }
    cnt += 1;
  }

  return cnt;
}
