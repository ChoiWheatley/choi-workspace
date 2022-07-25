#ifndef LIB_QUEUE
#define LIB_QUEUE

#include <memory>
#include <optional>

using std::shared_ptr;

template <typename E>
class Queue
{
public:
  Queue() = default;
  auto Enqueue(const E &element) -> void;
  auto Dequeue() -> std::optional<E>;
  auto size() const -> size_t;

protected:
  struct QueueElem
  {
    QueueElem(E &&value_) : next{nullptr}, value{std::move(value_)} {};
    QueueElem(E value_) : next{nullptr}, value{value_} {};
    shared_ptr<QueueElem> next;
    const E value;
  };

  shared_ptr<QueueElem> _head;
  shared_ptr<QueueElem> _tail;
};

#endif // LIB_QUEUE