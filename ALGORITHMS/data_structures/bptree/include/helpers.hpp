#include <memory>
#include <vector>

namespace bptree
{
  using std::vector;

  /// searchKey < [0]           THEN RETURN 0
  /// [N] <= searchKey < [N+1]  THEN RETURN N+1
  /// [M] <= searchKey          THEN RETURN M+1, M is Last index
  template <class Key>
  auto findIndexBetween(const vector<Key> &keys, const Key &searchKey) -> size_t
  {
    if (searchKey < keys[0])
    {
      return 0;
    }
    if (keys.back() <= searchKey)
    {
      return keys.size();
    }
    // O(N) search
    // TODO: make it O(log2(N))
    for (size_t i = 0; i < keys.size() - 1; ++i)
    {
      if (keys[i] <= searchKey && searchKey < keys[i + 1])
      {
        return i + 1;
      }
    }
    return static_cast<size_t>(-1);
  }
} // namespace bptree