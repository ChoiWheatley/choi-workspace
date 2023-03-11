#include "solution.hpp"
#include <ios>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::ios;
using std::string;

int main(void) {

  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string a;
  int power;
  cin >> a >> power;

  const auto bignum = BigNumber(a);
  auto submit = bignum;
  for (int i = 1; i < power; ++i) {

    submit = submit * bignum;
  }

  cout << submit.to_string() << "\n";

  return 0;
}