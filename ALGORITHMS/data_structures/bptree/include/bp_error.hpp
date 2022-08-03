#ifndef BP_ERROR
#define BP_ERROR

#include <cstdio>
#include <exception>

namespace bptree
{
  static constexpr size_t CHAR_MAX = 256;
  struct bp_error : public std::exception
  {
    virtual auto what() const noexcept -> const char * = 0;
  };
  struct no_key_found : bp_error
  {
    auto what() const noexcept -> const char * override { return "key is not found.\n"; }
  };
  struct node_overflow : bp_error
  {
    auto what() const noexcept -> const char * override { return "too many keys have been inserted.\n"; }
  };
  struct node_underflow : bp_error
  {
    auto what() const noexcept -> const char * override { return "the node has already zero keys!\n"; }
  };
  struct invalid_node : bp_error
  {
    auto what() const noexcept -> const char * override { return "node is invalid\n"; }
  };
  struct child_overflow : bp_error
  {
    auto what() const noexcept -> const char * override { return "too many child nodes have been inserted.\n"; }
  };
  struct child_underflow : bp_error
  {
    auto what() const noexcept -> const char * override { return "this have no child nodes.\n"; }
  };
  struct invalid_child : bp_error
  {
    auto what() const noexcept -> const char * override { return "did not passed child validation."; }
  };
  struct child_not_sorted : invalid_child
  {
    auto what() const noexcept -> const char * override
    {
      return "when attaching child nodes, make sure child nodes are already have sorted keys.\n";
    }
  };
  struct child_out_of_range : invalid_child
  {
    auto what() const noexcept -> const char * override
    {
      return "when attaching child nodes, make sure child nodes are actually in a key range.\n";
    }
  };
  struct child_is_missing : invalid_child
  {
    auto what() const noexcept -> const char * override
    {
      return "when validating, some child nodes are missing.\n";
    }
  };
}

#endif // BP_ERROR