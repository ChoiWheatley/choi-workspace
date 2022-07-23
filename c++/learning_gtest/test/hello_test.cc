#include <gtest/gtest.h>
#include <vector>
#include <iostream>

// Demonstrate some basic assertions
TEST(HelloTest, BasicAssertions)
{
  // Expect two strings not to be equal
  EXPECT_STRNE("hello", "world");
  // Expect equality
  EXPECT_EQ(7 * 6, 42);
}

TEST(Assertions, ExpectCondition)
{
  const auto x = std::vector<int>({1, 2, 3, 4, 4});
  const auto y = std::vector<int>({1, 2, 3, 4, 5});

  ASSERT_EQ(x.size(), y.size()) << "Vectors x and y are unequal length";
  for (int i = 0; i < x.size(); ++i)
  {
    EXPECT_EQ(x[i], y[i]) << "Vectors x and y differ at index[" << i << "]";
  }
  std::cerr << "여기에 도달할 수 있다\n";
}

TEST(Assertions, AbortCondition)
{
  const auto x = std::vector<int>({1, 2, 3, 4, 4});
  const auto y = std::vector<int>({1, 2, 3, 4});

  ASSERT_EQ(x.size(), y.size()) << "Vectors x and y are unequal length";
  for (int i = 0; i < x.size(); ++i)
  {
    EXPECT_EQ(x[i], y[i]) << "Vectors x and y differ at index[" << i << "]";
  }

  // just print some string
  std::cerr << "여기에 도달할 수 없다.\n";
}

TEST(Assertions, ExceptionCondition)
{
  // null pointer exception을 일부로 냈을 때?
  int *unsafe_ptr = nullptr;
  int something = *unsafe_ptr;

  std::cerr << "segmentation fault가 발생하고 실패로 간주한다.\n";
}