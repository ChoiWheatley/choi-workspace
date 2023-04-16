#include <cstddef>
#include <ios>
#include <iostream>
#include <map>
#define cr const &
using namespace std;
using u64 = unsigned long long;

u64 number_of_zeros(string cr str) {
  u64 cnt = 0;
  for (auto c : str) {
    if (c == '0') {
      cnt += 1;
    }
  }
  return cnt;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  u64 n, m;
  cin >> n >> m;

  map<string, u64, std::less<>> rows;
  for (size_t i = 0; i < n; ++i) {
    string line;
    cin >> line;
    rows[line] += 1;
  }

  u64 k;
  cin >> k;

  u64 optimal = 0;
  for (auto cr entry : rows) {
    auto cr row = entry.first;
    auto cr row_cnt = entry.second;
    auto cr zero_cnt = number_of_zeros(row);
    if (zero_cnt <= k && (k & 1) == (zero_cnt & 1)) {
      // k and zero_cnt are same odd or even
      optimal = std::max(optimal, row_cnt);
    }
  }

  cout << optimal << "\n";

  return 0;
}