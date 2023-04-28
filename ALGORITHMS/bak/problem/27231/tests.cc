#include <gtest/gtest.h>
#include <string>

TEST(Parse, Int) {
  std::string s = "023";
  int answer = 23;
  ASSERT_EQ(answer, std::stoi(s));
}