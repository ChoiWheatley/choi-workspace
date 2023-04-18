#include <algorithm>
#include <bitset>
#include <cstddef>
#include <ios>
#include <iostream>
#include <iterator>
#include <numeric>
#include <unordered_map>
#include <vector>

#define cr const &

constexpr size_t N = 2000;
constexpr size_t E = 1'000'000'000;

using namespace std;
using i64 = long long;
using idx_t = size_t;
using Map = unordered_map<i64, size_t>;
using BitSet = bitset<N>;

/**
@brief: find value from key, and mark as visited
*/
inline size_t map_search(Map &hashmap, i64 key) {
  auto itr = hashmap.find(key);
  if (itr != hashmap.end()) {
    size_t ret = itr->second;
    hashmap.erase(itr);
    return ret;
  }
  return 0;
}

inline size_t solution(vector<i64> &&ls) {
  Map hashmap;

  for (size_t i = 0; i < ls.size(); ++i) {
    auto cr e = ls[i];
    hashmap[e] += 1;
  }

  size_t cnt = 0;
  for (size_t i = 0; i < ls.size(); ++i) {
    for (size_t j = i + 1; j < ls.size(); ++j) {
      // corner case: zeros
      if (ls[i] == 0 && ls[j] == 0 && hashmap[0] <= 2) {
        continue;
      }
      auto sum = ls[i] + ls[j];
      // corner case: self
      if ((ls[i] == 0 || ls[j] == 0) && hashmap[sum] <= 1) {
        continue;
      }
      cnt += map_search(hashmap, sum);
    }
  }

  return cnt;
}