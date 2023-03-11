#include "solution.hpp"
#include <gtest/gtest.h>

TEST(BigNumber, Init) {
  auto num = BigNumber("12345");
  ASSERT_EQ("12345", num.to_string());
}
TEST(BigNumber, InitPoint) {
  const string str = "3.141592";
  auto num = BigNumber(str);
  ASSERT_EQ(str, num.to_string());
}
TEST(BigNumber, Multiply) {
  const string a = "3141592";
  const string b = "123";
  const string answer = "386415816";
  auto submit = BigNumber(a) * BigNumber(b);
  ASSERT_EQ(answer, submit.to_string());
}
TEST(BigNumber, Multiply2) {
  const string a = "3.141592";
  const string b = "123";
  const string answer = "386.415816";
  auto submit = BigNumber(a) * BigNumber(b);
  ASSERT_EQ(answer, submit.to_string());
}