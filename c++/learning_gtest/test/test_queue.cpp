/// https://google.github.io/googletest/primer.html#same-data-multiple-tests
/// test fixture 라는 이름의 공통객체를 만들어 여러 개의 테스트에서 공유하는 구성을 만들 수 있다.
#include <gtest/gtest.h>
#include <my_queue.hpp>
#include "QueueFixture.hpp"

/// Using fixture
TEST_F(QueueTest, IsEmptyInitially)
{
  EXPECT_EQ(0, q0_.size());
}

TEST_F(QueueTest, DequeueWorks1)
{
  auto n = q0_.Dequeue();
  EXPECT_FALSE(n.has_value());
}

TEST_F(QueueTest, DequeueWorks2)
{
  auto n = q1_.Dequeue();
  ASSERT_TRUE(n.has_value());
  EXPECT_EQ(1, *n);
  EXPECT_EQ(0, q1_.size());
  n.reset();
}

TEST_F(QueueTest, DequeueWorks3)
{
  auto n = q2_.Dequeue();
  ASSERT_TRUE(n.has_value());
  EXPECT_EQ(2, *n);
  EXPECT_EQ(1, q2_.size());
  n.reset();
}