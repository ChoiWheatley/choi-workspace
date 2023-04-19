#include "solution.hpp"
#include <ios>
#include <iostream>

using namespace std;
using std::vector;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t;
  cin >> t;

  for (int tc = 0; tc < t; ++tc) {

    int n, k, w;
    cin >> n >> k;

    vector<int> weights(n);
    for (int i = 0; i < n; ++i) {
      cin >> weights[i];
    }

    vector<Dependency> dependencies(k);
    for (int i = 0; i < k; ++i) {
      cin >> dependencies[i].dependee >> dependencies[i].depender;
    }

    cin >> w;

    int submit = solution(std::move(dependencies), std::move(weights), w);

    cout << submit << "\n";
  }

  return 0;
}