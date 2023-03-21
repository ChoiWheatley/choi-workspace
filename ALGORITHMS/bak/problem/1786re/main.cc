#include "solution.hpp"
#include <algorithm>
#include <ios>
#include <iostream>
#include <iterator>
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
  cout.tie(nullptr);

  string t;
  string p;
  std::getline(cin, t);
  std::getline(cin, p);

  vector<size_t> indices;

  auto kmp = Kmp(std::move(p));
  kmp.find(t, [&indices](size_t elem) { indices.push_back(elem + 1); });

  cout << indices.size() << "\n";

  std::for_each(indices.cbegin(), indices.cend(),
                [](auto e) { cout << e << ' '; });
  cout << "\n";

  return 0;
}