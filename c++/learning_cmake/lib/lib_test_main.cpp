#include <iostream>
#include <cstdint>

int add(const int &a, const int &b);

int main(void)
{
  std::cout << add(1, 2) << "\n";
  return 0;
}