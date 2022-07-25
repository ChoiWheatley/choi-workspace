#include <vector>
#include <cstdint>
#include <lib_arithmetic.h>

template <typename T>
inline T multiply(const T &a, const T &b)
{
  return a * b;
}
template int multiply(const int &a, const int &b);

template <typename T>
inline T divide(const T &a, const T &b)
{
  return a / b;
}
template int divide(const int &a, const int &b);

template <typename T>
inline T add(const T &a, const T &b)
{
  return a + b;
}
template int add(const int &a, const int &b);

template <typename T>
inline T subtract(const T &a, const T &b)
{
  return a - b;
}
template int subtract(const int &a, const int &b);

template <typename T>
inline T fibonacci(int order)
{
  static auto cache = std::vector<T>({0, 1});
  if (cache.size() <= order)
  {
    for (auto i = cache.size(); i <= order; ++i)
    {
      const auto elem = cache[i - 2] + cache[i - 1];
      cache.push_back(elem);
    }
  }
  return cache[order];
}
template auto fibonacci(int order) -> uint64_t;