#include "bp_error.hpp"
#include "bp_helpers.hpp"
#include <array>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

namespace bptree
{
  using std::array;
  using std::optional;
  using std::shared_ptr;

  /*
  AbstNode
  */
  template <class K, class R, size_t M>
  class AbstNode
  {
  public:
    // TODO: array<optional<T>,M>을 vector<T>로 바꾸자.
    virtual auto keys() const noexcept -> const vector<K> & = 0;
    virtual auto keyCount() const noexcept -> size_t = 0;
    virtual auto parent() const noexcept -> weak_ptr<AbstNode> = 0;
    // TODO: parent setter가 필요함
    virtual auto full() const noexcept -> bool = 0;
    virtual auto empty() const noexcept -> bool = 0;
    virtual auto validate() const noexcept -> bool = 0;
    virtual ~AbstNode(){};
  };

} // namespace bptree