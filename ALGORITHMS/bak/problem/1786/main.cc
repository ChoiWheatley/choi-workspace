#include "solution.hpp"
#include <algorithm>
#include <cstddef>
#include <ios>
#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::ios;
using std::string;
using std::vector;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string t;
  string p;
  std::getline(cin, t);
  std::getline(cin, p);

  auto kmp = Kmp(std::move(p));

  vector<size_t> matched_indices;
  auto on_match = [&matched_indices](size_t idx) {
    matched_indices.push_back(idx + 1);
  };

  kmp.compare_to(t, on_match);

  cout << matched_indices.size() << "\n";

  std::for_each(matched_indices.cbegin(), matched_indices.cend(),
                [](auto elem) { cout << elem << " "; });

  cout << "\n";

  return 0;
}