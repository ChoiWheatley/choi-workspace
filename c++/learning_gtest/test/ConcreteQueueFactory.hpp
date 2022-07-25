#include "AbstractQueueFactory.hpp"
#include <my_queue_impl.hpp>
#include <iostream>

template <typename E>
class QueueWithPrint : public Queue<E>
{
public:
  QueueWithPrint<E>() : Queue<E>(){};
  auto print() -> void
  {
    auto cursor = this->_head;
    std::cerr << "[ ";
    while (cursor != nullptr)
    {
      std::cerr << cursor->value << ", ";
      cursor = cursor->next;
    }
    std::cerr << " ]\n";
  }
  auto Enqueue(const E &element) -> void
  {
    Queue<E>::Enqueue(element);
    print();
  }
  auto Dequeue() -> std::optional<E>
  {
    const auto ret = Queue<E>::Dequeue();
    print();
    return ret;
  }
};

template <typename T>
class ConcreteQueueFactory : public AbstractQueueFactory<T>
{
public:
  auto getQueue() -> Queue<T> override
  {
    return QueueWithPrint<T>{};
  }
};