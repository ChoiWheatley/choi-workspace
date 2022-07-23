#include <gtest/gtest.h>
#include <lib_arithmetic.h>

TEST(Arithmetic, Fibonacci)
{
  using FIB_T = uint64_t;
  constexpr static auto answer = std::array<FIB_T, 21>({0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765});
  for (size_t i = 0; i < answer.size(); ++i)
  {
    EXPECT_EQ(fibonacci<FIB_T>(i), answer.at(i)) << "Fibonacci is wrong at index " << i;
  }
}