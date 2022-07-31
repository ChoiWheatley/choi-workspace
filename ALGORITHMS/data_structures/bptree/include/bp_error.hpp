#ifndef BP_ERROR
#define BP_ERROR

#include <exception>

namespace bptree
{
  struct bp_error : public std::exception
  {
    virtual auto what() const noexcept -> const char * = 0;
  };
  struct node_is_empty : bp_error
  {
    auto what() const noexcept -> const char * override { return "tree is empty.\n"; }
  };
  struct no_key_found : bp_error
  {
    auto what() const noexcept -> const char * override { return "key is not queried.\n"; }
  };
  struct node_overflow : bp_error
  {
    auto what() const noexcept -> const char * override { return "too much keys have been inserted.\n"; }
  };
  struct node_underflow : bp_error
  {
    auto what() const noexcept -> const char * override { return "the node has already zero keys!\n"; }
  };
  struct invalid_node : bp_error
  {
    auto what() const noexcept -> const char * override { return "node is invalid\n"; }
  };

}

#endif // BP_ERROR