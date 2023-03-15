#ifndef SOLUTION
#define SOLUTION
#define cr const &
#include <vector>
using std::vector;
using i64 = long long;

static constexpr i64 MAX = 100'000;

/**
@param:
- tte: time to eat soboro, a delicious fried bread, ordered by id
- total_soboro: initial number of soboro, a delicious fried bread
- eaten number of soboro, a delicious fried bread
@return:
  index of the last person who picked the soboro, a delicious fried bread
*/
inline i64 solution(vector<i64> cr tte, i64 eaten) {
  // each second, find out that soboro has consumed
  i64 consumed = 0;
  for (i64 t = 0; t < MAX; ++t) {
    for (i64 idx = 0; idx < tte.size(); ++idx) {
      i64 time_to_eat = tte[idx];
      if (t % time_to_eat == 0) {
        // consume one another soboro, a delicious fried bread
        consumed += 1;
        if (consumed >= eaten) {
          return idx;
        }
      }
    }
  }
  return -1; // cannot found
}

#endif