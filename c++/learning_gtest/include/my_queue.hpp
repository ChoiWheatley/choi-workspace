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

/// Queue Methods

template <typename E>
auto Queue<E>::Enqueue(const E &element) -> void
{
  if (_head == nullptr)
  {
    _head = std::make_shared<QueueElem>(element);
    _tail = _head;
  }
  else
  {
    const auto old_tail = _tail;
    _tail = std::make_shared<QueueElem>(element);
    old_tail->next = _tail;
  }
}

template <typename E>
auto Queue<E>::Dequeue() -> std::optional<E>
{
  if (_head == nullptr)
  {
    return std::nullopt;
  }
  const auto old_head = _head;
  const auto ret = old_head->value;
  _head = old_head->next;
  old_head->next.reset();

  return ret;
}

template <typename E>
auto Queue<E>::size() const -> size_t
{
  auto cnt = static_cast<size_t>(0);
  auto cursor = _head;
  while (cursor != nullptr)
  {
    cursor = cursor->next;
    ++cnt;
  }
  return cnt;
}
#endif // LIB_QUEUE