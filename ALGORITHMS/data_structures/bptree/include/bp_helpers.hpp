#ifndef BP_HELPERS
#define BP_HELPERS

#include <array>
#include <cmath>
#include <vector>

namespace bptree
{
  using std::array;
  using std::vector;
  using index_t = size_t;

  /// insert 시 발생한 오버플로를 ceil(M/2) 크기의 벡터로 쪼갠다.
  // template <class Key, size_t M>
  // auto unsaturate(const vector<Key> &saturated) noexcept -> vector<array<index_t, M>> {}

  /// node가 LeafNode인지 확인한다.
  // template <class Key, class Record, size_t M>
  // inline auto isLeaf(AbstNode<Key, Record, M> *node) -> bool {}

  /// key와 일치하거나 들어갈 수 있는 리프노드를 리턴한다.
  // template <class Key, class Record, size_t M>
  // auto tour(const Key &key, shared_ptr<AbstNode<Key, Record, M>> pRoot) -> const shared_ptr<LeafNode<Key, Record, M>> {}

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

  template <typename T>
  auto maxIdxLessThan(T given, const vector<T> &from, bool equal = false) noexcept -> index_t
  {
    const auto key = given;
    const auto keys = from;
    const auto size = keys.size();
    // 낑겨들어갈 index 찾기
    size_t left = 0;
    size_t right = size;
    size_t idx = static_cast<size_t>((left + right) / 2);
    while (left < right)
    {
      const auto &val = from.at(idx);
      if (val < key)
      // move right
      {
        left = (left == idx) ? (left + 1) : idx;
      }
      else if (key < val)
      // move left
      {
        right = (right == idx) ? (right - 1) : idx;
      }
      else /* key == val */
      {
        // 여러개가 있을 수 있으므로
        equal ? right -= 1 : left += 1;
      }
      idx = static_cast<size_t>(ceil(((double)left + (double)right) / 2));
    }
    return idx;
  }

  template <typename T>
  auto minIdxLargerThan(T given, const vector<T> &from, bool equal = false) noexcept -> index_t
  {
    const auto key = given;
    const auto keys = from;
    const auto size = keys.size();
    // 낑겨들어갈 index 찾기
    size_t left = 0;
    size_t right = size;
    size_t idx = static_cast<size_t>((left + right) / 2);
    while (left < right)
    {
      const auto &val = keys.at(idx);
      if (val < key)
      // move right
      {
        left = (left == idx) ? (left + 1) : idx;
      }
      else if (key < val)
      // move left
      {
        right = (right == idx) ? (right - 1) : idx;
      }
      else /* key == val */
      {
        // 여러개 있을 수 있으므로 좌 또는 우로 한칸씩
        equal ? right -= 1 : left += 1;
      }
      idx = static_cast<size_t>((left + right) / 2);
    }
    return idx;
  }

} // namespace bptree

#endif // BP_HELPERS