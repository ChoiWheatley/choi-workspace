#include <gtest/gtest.h>
#include <memory>

TEST(Shared, Pointer)
{
  std::shared_ptr<int> pSomething{nullptr};
  EXPECT_EQ(pSomething.get(), nullptr);
  EXPECT_EQ(pSomething.use_count(), 0);
}