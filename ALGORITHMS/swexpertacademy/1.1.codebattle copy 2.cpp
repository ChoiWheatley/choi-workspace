
/*
 * https://swexpertacademy.com/main/talk/codeBattle/problemDetail.do?contestProbId=AYHSEfgq_1wDFATO&categoryId=AYHWVZMqQWEDFATO&categoryType=BATTLE&battleMainPageIndex=1
 *
 * 같은 땅의 기준: 4-way
 * subIsland 개념으로 각 Island만을 잘라다 작은 region들의 집합을 만든다. 
 * countIslands()는 subIsland의 원소의 수만 세는 아주 간단한 함수.
 * subIslands_k = { subDivide((region-k)[s]) | s is element of subIslands_(k-1) }
 * 이때, k는 이터레이션 횟수를 의미한다. 
 * 이때, operator-(region, k) 같은 경우는 물을 한 칸씩 채우는 flood()와 동일하다.
 * 이때, s의 타입은 vector<Idx>로, region의 인덱스를 저장한다.
 * 이 이터레이션은 subIslands의 원소가 빌 때까지 반복한다.
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <map>
#if DBG == 1
#include <cstdio>
#endif

using namespace std;

auto scan() -> vector<int> {
  auto region = vector<int>();
  auto n = 0;
  cin >> n;
  auto nsqared = n * n;

  while (nsqared--) {
    auto e = 0;
    cin >> e;
    region.push_back(e);
  }

  return region;
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
  auto isValid(const int size) const -> bool {
    const auto side = static_cast<int>(sqrt(size));
    if (this->y < 0 || this->x < 0 || this->y >= side || this->x >= side) {
      return false;
    }
    return true;
  }
  auto operator<(const Point& other) const -> bool {
    if (this->y < other.y) {
      return false;
    }
    if (other.y < this->y) {
      return true;
    }
    if (this->y == other.y) {
      if (this->x < other.x) {
        return false;
      }
      if (other.x < this->x) {
        return true;
      }
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
  if (!point.isValid(size)) {
    return -1;
  }
  return (side * point.y + point.x);
}

auto convertPointFrom(const int idx, const int size) -> Point {
  const auto side = static_cast<int>(sqrt(size));
  if (idx < 0 || size < idx) {
    return Point{.y = -1, .x = -1};
  }
  return Point{.y = static_cast<int>(idx / side), .x = idx % side};
}

auto countIslands(const set<vector<Point>>& subIslands) -> int {
  return subIslands.size();
}

auto flood(const vector<int> &region, const int amount) -> vector<int> {
  auto ret = vector<int>{region};
  for (auto i = 0; i < ret.size(); ++i) {
    ret[i] -= amount;
  }
  return ret;
}

auto flood(const vector<int> &region) -> vector<int> {
  return flood(region, 1);
}

auto operator-(const vector<int>& region, const int amount) -> vector<int> {
  return flood(region, amount);
}

auto makeSubIsland(const vector<int>& visitStat) -> set<vector<Point>> {
  /// 1 1 0 0
  /// 1 1 0 0
  /// 0 0 2 2
  /// 0 0 2 2
  /// => set{ [(0,0),(0,1),(1,0),(1,1)], [(2,2),(2,3),(3,2),(3,3)] }
  /// visitStat은 보기보다 클 수 있다.
  const auto MAX_ISLANDS = 5000;
  const auto size = visitStat.size();
  const auto side = static_cast<int>(sqrt(size));

  auto dictionary = map<int, vector<Point>>{};
  for (auto i = 0; i < size; ++i) {
    const auto islandNo = visitStat[i];
    if (islandNo <= 0) {
      continue;
    }
    const auto coord = convertPointFrom(i, size);
    dictionary[islandNo].push_back(coord);
  }

  // MARK: 검증이 필요하다.
  return [dictionary]() -> set<vector<Point>> {
    auto ret = set<vector<Point>>{};
    for (const auto& i : dictionary) {
      ret.insert(i.second);
    }
    return ret;
  }();
}

auto subDivide(const vector<int>& region, const set<vector<Point>>& subIslands) -> set<vector<Point>> {
  /// 좌상단에서부터 세기 시작한다. 값이 양수이고 처음 만나는 원소인 경우
  /// 다녀감으로 표시한 뒤 좌, 우, 하 순서로 스택에 집어넣는다.
  /// currentCount 값에 따라 해당 영역의 번호가 정해진다.
  const auto NOT_VISITED = -1;
  const auto SEA = 0;
  const auto size = region.size();
  const auto side = static_cast<int>(sqrt(size));
  auto ret = set<vector<Point>>{};

  for (const auto points : subIslands) {
    auto currentCount = 0;
    auto visitStat = vector<int>(size, NOT_VISITED);
    auto moveStack = stack<Point>();

    for (const auto point : points) {
      const auto idx = convertIndexFrom(point, size);

      if (idx < 0) {
        // something is wrong!
        return set<vector<Point>>{};
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

    // visitStat을 보고 subIsland를 만들어낸다.
    const auto subIsland = makeSubIsland(visitStat);
    ret.insert(subIsland.begin(), subIsland.end());
  }
  return ret;
}

/// subIsland_k = { subDivide((region-k)[s]) | s is element of subIslands_(k-1) }
auto solve(const vector<int> &region) -> int {

  const auto size = region.size();
  const auto side = static_cast<int>(sqrt(size));
  auto best = 0;
  auto currentRegion = vector<int>{region};
  // [ (0,0), (0,1), ... , (N-1,N-1) ]
  auto currentSubIslands = set<vector<Point>>{[side]() -> vector<Point> {
    auto ret = vector<Point>{};
    for (auto j = 0; j < side; ++j) {
      for (auto i = 0; i < side; ++i) {
        ret.push_back(Point{j,i});
      }
    }
    return ret;
  }()};

  while (!currentSubIslands.empty()) {
    currentRegion = currentRegion - 1;
    currentSubIslands = subDivide(currentRegion, currentSubIslands);
    const auto cnt = countIslands(currentSubIslands);
    if (best < cnt) {
      best = cnt;
    }
  }
  return best;
}

int main() {
#if DBG == 1
  freopen("input.txt", "r", stdin);
#endif

  int test_case;
  int T;
  cin >> T;

  for (test_case = 1; test_case <= T; ++test_case) {
    const auto scaned = scan();
    cout << "#" << test_case << " " << solve(scaned) << "\n";
  }

  return 0;
}
