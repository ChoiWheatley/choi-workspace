#include <iostream>

extern int fibonacci(int);

int main(int argc, char **argv)
{
  std::cout << "Hello, World\n";
  std::cout << "fib(1...100) : \n";
  for (int i = 1; i <= 100; ++i)
  {
    std::cout << "fib(" << i << ") = " << fibonacci(i) << "\n";
  }
  return 0;
}