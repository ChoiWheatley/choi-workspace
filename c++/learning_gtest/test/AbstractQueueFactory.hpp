#ifndef ABSTRACT_QUEUE_FACTORY
#define ABSTRACT_QUEUE_FACTORY

#include <my_queue.hpp>

template <typename T>
class AbstractQueueFactory
{
public:
  AbstractQueueFactory<T>() = default;
  virtual auto getQueue() -> Queue<T> = 0;
};

#endif