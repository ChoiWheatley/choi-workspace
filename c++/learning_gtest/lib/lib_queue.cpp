#include <lib_queue.h>

template <typename E>
struct QueueElem
{
  std::shared_ptr<E> next;
  const E value;
};

template <typename E>
class QueueImpl : public Queue<E>
{
public:
  QueueImpl();
  virtual auto Enqueue(const E &element) -> void = 0;
  virtual auto Dequeue() -> std::optional<E> = 0;
  virtual auto size() const -> size_t = 0;

private:
  std::shared_ptr<QueueElem<E>> _head;
  std::shared_ptr<QueueElem<E>> _tail;
};

/// QueueFactory Methods
template <typename E>
QueueFactory<E>::QueueFactory()
    : _queue{std::make_shared<QueueImpl<E>{}>} {}

template <typename E>
auto QueueFactory<E>::queue() -> std::shared_ptr<Queue<E>>
{
  return _queue;
}

/// QueueImpl Methods
template <typename E>
QueueImpl<E>::QueueImpl() : Queue<E>{} {}

template <typename E>
auto QueueImpl<E>::Enqueue(const E &element) -> void
{
  if (_head == nullptr)
  {
    _head = std::make_shared(QueueElem{.next = nullptr, .value = element});
    _tail = _head;
  }
  else
  {
    const auto old_tail = _tail;
    _tail = std::make_shared(QueueElem{.next = nullptr, .value = element});
    old_tail->next = _tail;
  }
}