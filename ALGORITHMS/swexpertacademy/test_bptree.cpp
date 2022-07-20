#include <gtest/gtest.h>

TEST(HelloTest, BasicAssertions)
{
  EXPECT_STRNE("Hello", "world");

  EXPECT_EQ(7 * 6, 42);
}