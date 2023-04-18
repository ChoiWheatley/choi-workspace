#include "solution.hpp"
#include <algorithm>
#include <gtest/gtest.h>
#include <initializer_list>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

inline void do_test(initializer_list<int> list, int m, string cr answer) {
  auto sstream = stringstream();
  auto submit = solution(list, m);
  for_each(submit.crbegin(), submit.crend(),
           [&](auto cr e) { sstream << to_string(e); });
  if (submit.empty()) {
    sstream << '0';
  }
  ASSERT_EQ(answer, sstream.str());
}

TEST(Sol, 1) { do_test({6, 7, 8}, 21, "210"); }
TEST(Sol, 2) { do_test({5, 23, 24}, 30, "20"); }
TEST(Sol, 3) { do_test({1, 5, 3, 2}, 1, "0"); }
TEST(Sol, 4) {
  do_test({1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 50,
          "99999999999999999999999999999999999999999999999999");
}
TEST(Sol, 5) { do_test({1, 2, 3, 4, 5}, 15, "10000000000000"); }
TEST(Sol, 6) { do_test({1, 5, 3, 2}, 2, "3"); }
TEST(Sol, 7) {
  do_test({50, 50, 1}, 50,
          "22222222222222222222222222222222222222222222222222");
}
TEST(Sol, 8) { do_test({1, 50}, 50, "1"); }
TEST(Sol, 9) { do_test({6, 7, 8}, 22, "220"); }
TEST(Sol, 10) { do_test({10}, 20, "0"); }
TEST(Sol, 11) { do_test({6, 7, 8}, 6, "0"); }
TEST(Sol, 12) { do_test({1, 2, 2, 3, 3}, 20, "2000000000000000000"); }
TEST(Sol, 13) { do_test({10, 30, 50}, 20, "0"); }
TEST(Sol, 14) { do_test({6, 32, 38, 18, 12, 6, 7, 8, 6, 7}, 50, "99888888"); }
TEST(Sol, 15) { do_test({1, 1}, 1, "1"); }
TEST(Sol, 16) { do_test({1, 1, 1, 1, 1, 10}, 10, "4444444444"); }
TEST(Sol, 17) { do_test({1}, 1, "0"); }
TEST(Sol, 18) { do_test({2, 1}, 10, "1111111111"); }
TEST(Sol, 19) { do_test({2, 1, 1}, 10, "2222222222"); }
TEST(Sol, 20) { do_test({2, 1, 1, 2}, 10, "2222222222"); }
TEST(Sol, 21) { do_test({9, 7, 8, 9}, 20, "33"); }