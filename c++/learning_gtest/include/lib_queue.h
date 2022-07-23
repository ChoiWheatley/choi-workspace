#ifndef LIB_QUEUE
#define LIB_QUEUE

#include <memory>
#include <optional>

template <typename E>
class Queue
{
public:
  Queue();
  virtual auto Enqueue(const E &element) -> void = 0;
  virtual auto Dequeue() -> std::optional<E> = 0;
  virtual auto size() const -> size_t = 0;
};

template <typename E>
class QueueFactory
{
public:
  QueueFactory();
  auto queue() -> std::shared_ptr<Queue<E>>;

private:
  std::shared_ptr<Queue<E>> _queue;
};

#endif // LIB_QUEUE