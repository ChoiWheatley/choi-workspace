#include <iostream>
#include <cstdint>
#include <lib_arithmetic.h>

int main(int argc, char **argv)
{
  std::cout << "Hello, World\n";
  std::cout << "fib(1...100) : \n";
  for (int i = 1; i <= 20; ++i)
  {
    std::cout << "fib(" << i << ") = " << fibonacci<uint64_t>(i) << "\n";
  }
  return 0;
}