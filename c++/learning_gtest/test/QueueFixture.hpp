/*
이 코드는 프레임워크에 해당하는 코드가 되었다. Dependency Injection을 수행한다.
*/
#include <memory>
#include <gtest/gtest.h>
#include "AbstractQueueFactory.hpp"
#include "ConcreteQueueFactory.hpp"

/// Creating fixture
class QueueTest : public ::testing::Test
{
protected:
  QueueTest() : _factory{std::make_unique<ConcreteQueueFactory<int>>()}
  {
    // Dependency Injection | Inverse Of Control
    q0_ = _factory->getQueue();
    q1_ = _factory->getQueue();
    q2_ = _factory->getQueue();
  }
  void SetUp() override
  {
    std::cerr << "Hello, Queue!";
    q1_.Enqueue(1);
    q2_.Enqueue(2);
    q2_.Enqueue(3);
  }
  void TearDown() override
  {
    // Do nothing?
    std::cerr << "I'm gonna be destructed soon!\n";
  }

  Queue<int> q0_;
  Queue<int> q1_;
  Queue<int> q2_;

private:
  std::unique_ptr<AbstractQueueFactory<int>> _factory = nullptr;
};
