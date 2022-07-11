
/*
 * https://swexpertacademy.com/main/talk/codeBattle/problemDetail.do?contestProbId=AYHSEfgq_1wDFATO&categoryId=AYHWVZMqQWEDFATO&categoryType=BATTLE&battleMainPageIndex=1
 *
 * 같은 땅의 기준: 4-way
 * N*N 지형이 이미 주어졌을 때 물을 한 칸씩 채우면서 발생하는 영역을 다 세면
 * 되지 않을까
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

auto scan() -> vector<vector<int>> {
  auto ret = vector<vector<int>>();
  auto testcases = 0;
  cin >> testcases;

  while (testcases--) {
    auto region = vector<int>();
    auto n = 0;
    cin >> n;
    auto nsqared = n * n;

    while (nsqared--) {
      auto e = 0;
      cin >> e;
      region.push_back(e);
    }
    ret.push_back(region);
  }
  return ret;
}

auto operator<<(ostream& os, const vector<int>& region) -> ostream& {
  const auto size = region.size();
  const auto side = static_cast<int>(sqrt(size));
  auto cnt = 0;

  os << "[\n";
  for (auto i : region) {
    os << i << " ";
    if (++cnt % side == 0) {
      os << "\n";
    }
  }
  os << "]\n";

  return os;
}

auto operator<<(ostream& os, const vector<vector<int>>& scaned) -> ostream& {
  for (auto i : scaned) {
    os << i;
  }
  return os;
}

struct Point {
  int y;
  int x;
  auto up() const -> Point {
    return Point{.y = this->y - 1, .x = this->x};
  }
  auto right() const -> Point {
    return Point{.y = this->y, .x = this->x + 1};
  }
  auto left() const -> Point {
    return Point{.y = this->y, .x = this->x - 1};
  }
  auto down() const -> Point {
    return Point{.y = this->y + 1, .x = this->x};
  }
  auto isValidate(const int size) const -> bool {
    const auto side = static_cast<int>(sqrt(size));
    if (this->y < 0 || this->x < 0 || this->y >= side || this->x >= side) {
      return false;
    }
    return true;
  }
};

auto operator<<(ostream& os, const Point& pnt) -> ostream& {
  os << "(" << pnt.y << "," << pnt.x << ")";
  return os;
}


auto convertIndexFrom(const Point point, const int size) -> int {
  const auto side = static_cast<int>(sqrt(size));
  if (!point.isValidate(size)) {
    return -1;
  }
  return (side * point.y + point.x);
}

auto countIslands(const vector<int> &region) -> int {
  /// 좌상단에서부터 세기 시작한다. 값이 양수이고 처음 만나는 원소인 경우
  /// 다녀감으로 표시한 뒤 좌, 우, 하 순서로 스택에 집어넣는다.
  /// currentCount 값에 따라 해당 영역의 번호가 정해진다.
  const auto NOT_VISITED = -1;
  const auto SEA = 0;
  const auto size = region.size();
  const auto side = static_cast<int>(sqrt(size));

  auto currentCount = 0;
  auto visitStat = vector<int>(region.size(), NOT_VISITED);
  auto moveStack = stack<Point>();

  for (auto j = 0; j < side; ++j) {
    for (auto i = 0; i < side; ++i) {
      const auto point = Point{.y = j, .x = i};
      const auto idx = convertIndexFrom(point, region.size());

      // DEBUG
      /* cout << "current point : " << point << "\n"; */
      /* cout << "current visitStat : " << visitStat << "\n"; */

      if (idx < 0) {
        // something is wrong!
        return -1;
      }
      if (visitStat[idx] != NOT_VISITED) {
        continue;
      }
      if (region[idx] <= 0) {
        visitStat[idx] = SEA;
        continue;
      }
      visitStat[idx] = ++currentCount;
      // 처음엔 오른쪽과 하단에만 스택에 넣어놓으면 된다.
      moveStack.push(point.down());
      moveStack.push(point.right());

      while (!moveStack.empty()) {
        const auto nextPoint = Point{moveStack.top()};
        moveStack.pop();

        // DEBUG
        // cout << "visitStat : " << visitStat;


        const auto idx = convertIndexFrom(nextPoint, size);
        if (idx < 0) {
          // index is not valid
          continue;
        }
        if (visitStat[idx] != NOT_VISITED) {
          continue;
        }
        if (region[idx] <= 0) {
          visitStat[idx] = SEA;
          continue;
        }
        visitStat[idx] = currentCount;

        moveStack.push(nextPoint.up());
        moveStack.push(nextPoint.down());
        moveStack.push(nextPoint.right());
        moveStack.push(nextPoint.left());


      }
    }
  }

  return currentCount;
}

auto flood(const vector<int> &region) -> const vector<int> {
  auto ret = vector<int>{region};

  for (auto i = 0; i < ret.size(); ++i) {
    ret[i]--;
  }

  return ret;
}

auto isFloodingDone(const vector<int> &region) -> bool {
  for (auto i : region) {
    if (i >= 0) {
      return false;
    }
  }
  return true;
}

auto solve(const vector<int> &region) -> int {
  auto best = 0;
  auto currentRegion = vector<int>{region};

  while (!isFloodingDone(currentRegion)) {
    const auto current = countIslands(currentRegion);
    if (best < current) {
      best = current;
    }
    currentRegion = flood(currentRegion);
  }

  return best;
}

int main() {
  const auto scaned = scan();
  /* cout << scaned << "\n"; */

  auto count = 1;
  for (auto i : scaned) {
    cout << "#" << count++ << " " << solve(i) << "\n";
  }
}
