#include <iostream>
#include <string>
#include <cstdint>
#include <memory>
#include <lib_arithmetic.h>
#include <my_queue.hpp>

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

int main(int argc, char **argv)
{
  std::cout << "Hello, World\n";
  std::cout << "fib(1...100) : \n";
  for (int i = 1; i <= 20; ++i)
  {
    std::cout << "fib(" << i << ") = " << fibonacci<uint64_t>(i) << "\n";
  }

  const auto string = std::string{"Hello, Queue"};
  std::cout << string << "\n";

  auto q = QueueWithPrint<char>{};
  for (const auto &c : string)
  {
    q.Enqueue(c);
  }

  while (true)
  {
    const auto elem = q.Dequeue();
    if (!elem.has_value())
      break;
    std::cout << "(" << elem.value() << ")";
  }

  return 0;
}