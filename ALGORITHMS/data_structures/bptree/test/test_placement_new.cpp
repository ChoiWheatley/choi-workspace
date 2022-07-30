#include <gtest/gtest.h>
#include <memory>

TEST(Placement, New)
{
  int *pSomethingInt = new int(1);
  ASSERT_EQ(*pSomethingInt, 1);
  int *pOtherInt = new (pSomethingInt) int(2); // placement new
  ASSERT_EQ(*pOtherInt, 2);
  // check both pointers have same address
  EXPECT_EQ(pSomethingInt, pOtherInt);
}

TEST(Placement, SharedPointer)
{
  auto pSomethingInt = std::make_shared<int>(1);
  ASSERT_EQ(*pSomethingInt, 1);
  // auto pOtherInt = std::shared_ptr<int>(new (pSomethingInt.get()) int(2)); // double free
  auto pOtherInt = new (pSomethingInt.get()) int(2);
  ASSERT_EQ(*pOtherInt, 2);
  // check both pointers have same address
  EXPECT_EQ(pSomethingInt.get(), pOtherInt);
  EXPECT_EQ(*pSomethingInt, *pOtherInt);
}