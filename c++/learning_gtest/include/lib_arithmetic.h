#ifndef LIB_ARITHMETIC
#define LIB_ARITHMETIC
// INTERFACE

template <typename T>
extern T multiply(const T &a, const T &b);

template <typename T>
extern T divide(const T &a, const T &b);

template <typename T>
extern T add(const T &a, const T &b);

template <typename T>
extern T subtract(const T &a, const T &b);

template <typename T = uint64_t>
extern T fibonacci(int order);

#endif // LIB_ARITHMETIC