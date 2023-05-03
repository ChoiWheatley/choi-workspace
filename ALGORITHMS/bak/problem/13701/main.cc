#include <bitset>
#include <ios>
#include <iostream>

using namespace std;

constexpr int MAX_N = 1 << 25;

static bitset<MAX_N> bins;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  unsigned long a;
  while (!(cin >> a).eof()) {
    if (!bins.test(a)) {
      bins.set(a);
      cout << a << ' ';
    }
  }
  cout << "\n";

  return 0;
}