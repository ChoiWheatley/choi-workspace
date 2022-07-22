extern auto add(const int &a, const int &b) -> int;

auto fibonacci(int order) -> int
{
  if ((order == 0) | (order == 1))
  {
    return 1;
  }
  int before = 1, after = 1;
  for (auto i = 2; i <= order; ++i)
  {
    const auto tmp = after;
    after = add(after, before);
    before = tmp;
  }
  return after;
}