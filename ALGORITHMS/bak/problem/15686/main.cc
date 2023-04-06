#include <ios>
#include <iostream>
#include <stddef.h>
#include <vector>
using namespace std;
#define cr const &
constexpr int MAX_DIST = 99999;

class CityBuilder;
class City;
class VirtualCity;
class ICity;

struct Point {
  int i;
  int j;
};

struct Chicken {
  Point pos;
  bool is_alive = true;
  explicit Chicken(int i, int j) : pos(Point{i, j}) {}
};

// get manhattan distance
inline auto operator-(Point cr lhs, Point cr rhs) -> int {
  return std::abs(lhs.i - rhs.i) + std::abs(lhs.j - rhs.j);
}

inline auto get_chicken_dist(vector<Point> cr houses,
                             vector<Chicken> cr chickens) {
  int sum = 0;
  for (auto cr house : houses) {
    int min_dist = MAX_DIST;
    for (auto cr chicken : chickens) {
      if (chicken.is_alive) {
        min_dist = std::min(min_dist, house - chicken.pos);
      }
    }
    sum += min_dist;
  }
  return sum;
}

inline auto alive_chickens(vector<Chicken> cr chickens) -> int {
  int cnt = 0;
  for (auto chicken : chickens) {
    if (chicken.is_alive) {
      cnt++;
    }
  }
  return cnt;
}

auto solution(vector<Point> cr houses, vector<Chicken> &chickens, int m,
              int idx) -> int {
  if (alive_chickens(chickens) == m) {
    return get_chicken_dist(houses, chickens);
  }
  int local_best = MAX_DIST;
  for (size_t i = idx; i < chickens.size(); ++i) {
    auto &chicken = chickens[i];
    if (chicken.is_alive) {
      chicken.is_alive = false;

      int result = solution(houses, chickens, m, //
                            int(i + 1)); // 여기에서 중복을 줄일 수 있다.
      local_best = std::min(local_best, result);

      chicken.is_alive = true;
    }
  }
  return local_best;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<Point> houses;
  vector<Chicken> chickens;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int input;
      cin >> input;
      switch (input) {
      case 1: {
        houses.push_back(Point{i, j});
        break;
      }
      case 2: {
        chickens.push_back(Chicken{i, j});
        break;
      }
      default: {
        break;
      }
      }
    }
  }

  int submit = solution(houses, chickens, m, 0);

  cout << submit << "\n";

  return 0;
}