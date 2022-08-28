#ifndef HELPERS
#define HELPERS

#include <cmath>
#include <memory>
#include <tuple>
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
    if (keys.empty())
    {
      return 0;
    }
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
    // ERROR
    return static_cast<size_t>(-1);
  }

  /// split long vector into two half-sized (first one is smaller if size is odd) vectors
  template <class _T>
  auto split(const vector<_T> &vec) -> std::pair<vector<_T>, vector<_T>>
  {
    const size_t halfIndex = static_cast<size_t>(floor(double(vec.size()) / 2.0f));

    auto left = vector<_T>{
        vec.begin(),
        vec.begin() + halfIndex};
    auto right = vector<_T>{
        vec.begin() + halfIndex,
        vec.end()};

    return std::make_pair(left, right);
  }

} // namespace bptree

#endif // HELPERS