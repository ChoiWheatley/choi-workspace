
#include <ios>
#include <iostream>
#include <istream>
using std::cin;
using std::cout;
using std::ios;
using std::istream;

constexpr static int MAX_HZ = 999999;

constexpr int dist(int lhs, int rhs) {
  if (lhs < rhs) {
    return rhs - lhs;
  }
  return lhs - rhs;
}

int solution(int a, int b, int n, istream &is) {

  int min_dist = MAX_HZ;

  for (int i = 0; i < n; ++i) {

    int each_button;
    is >> each_button;

    if (dist(each_button, b) < min_dist) {

      min_dist = dist(each_button, b);
    }
  }

  return dist(a, b) <= min_dist ? dist(a, b) : min_dist + 1;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int a;
  int b;
  int n;
  cin >> a >> b >> n;

  int submit = solution(a, b, n, cin);

  cout << submit << "\n";

  return 0;
}