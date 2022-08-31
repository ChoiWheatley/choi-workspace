#include <gtest/gtest.h>
#include <stack>

TEST(Stack, EmptyTop)
{
  std::stack<int> myStack;
  myStack.push(5);
  EXPECT_EQ(5, myStack.top());
  myStack.pop();
  EXPECT_EQ(0, myStack.size());
  // myStack.pop(); // undefined behavior
}

TEST(Stack, EmptyStack)
{
  auto fakeStack = std::stack<int>{/*empty*/};
  EXPECT_TRUE(fakeStack.empty());
}