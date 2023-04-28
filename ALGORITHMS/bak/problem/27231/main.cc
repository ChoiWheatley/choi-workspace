#include "solution.hpp"
#include <ios>
#include <iostream>

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t;
  cin >> t;
  for (int tc = 0; tc < t; ++tc) {
    int input;
    cin >> input;
    auto result = solution(input);
    if (result == INFINITE) {
      cout << "Hello, BOJ 2023!\n";
    } else {
      cout << result << "\n";
    }
  }

  return 0;
}