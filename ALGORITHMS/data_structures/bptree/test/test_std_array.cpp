#include <gtest/gtest.h>
#include <array>

TEST(Array, Size)
{
  std::array<int, 5> container{1, 2, 3, 4, 5};
  EXPECT_EQ(container.size(), 5);
  std::array<int, 5> emptyContainer{};
  EXPECT_EQ(emptyContainer.size(), 5);
}
