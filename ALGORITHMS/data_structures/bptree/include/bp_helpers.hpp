#ifndef BP_HELPERS
#define BP_HELPERS

#include <vector>

namespace bptree
{
  template <typename T>
  auto operator<(const std::vector<T> &group, const T &compareTo) -> bool
  /// all group element must be smaller than `compareTo`
  {
    for (const auto element : group)
    {
      if (compareTo <= element)
      {
        return false;
      }
    }
    return true;
  }

  template <typename T>
  auto operator<=(const std::vector<T> &group, const T &compareTo) -> bool
  /// all group element must be smaller or equal than `compareTo`
  {
    for (const auto element : group)
    {
      if (compareTo < element)
      {
        return false;
      }
    }
    return true;
  }

} // namespace bptree

#endif // BP_HELPERS