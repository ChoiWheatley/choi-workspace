#include "my_queue.hpp"

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