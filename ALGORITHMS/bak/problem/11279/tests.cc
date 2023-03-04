#include "solution.hpp"
#include <gtest/gtest.h>
#include <limits>
#include <random>
#include <string>

TEST(MAXHEAP, Hello) {
  MaxHeap heap{};
  ASSERT_EQ(0, heap.get_max());
  heap.add(1);
  ASSERT_EQ(1, heap.get_max());
  heap.add(2);
  ASSERT_EQ(2, heap.get_max());
  ASSERT_EQ(2, heap.pop_max());
  ASSERT_EQ(1, heap.pop_max());
  ASSERT_EQ(0, heap.pop_max());
  ASSERT_EQ(0, heap.pop_max());
  ASSERT_EQ(0, heap.pop_max());
  ASSERT_EQ(0, heap.pop_max());
  heap.add(3);
  heap.add(2);
  heap.add(1);
  ASSERT_EQ(3, heap.pop_max());
  ASSERT_EQ(2, heap.pop_max());
  ASSERT_EQ(1, heap.pop_max());
  ASSERT_EQ(0, heap.pop_max());
  int max_int = std::numeric_limits<int>::max() - 1;
  heap.add(max_int);
  ASSERT_EQ(max_int, heap.pop_max());
}

TEST(MAXHEAP, sol2) {
  MaxHeap heap{};
  heap.add(100);
  heap.add(19);
  heap.add(36);
  heap.add(7);
  heap.add(3);
  heap.add(25);
  heap.add(1);

  int max = heap.pop_max();
  while (!heap.is_empty()) {
    int next_max = heap.pop_max();
    ASSERT_TRUE(max >= next_max);
    max = next_max;
  }
}

TEST(MAXHEAP, sol3) {
  MaxHeap heap{};
  heap.add(100).add(99).add(10).add(1).add(2).add(8).add(9);

  int max = heap.pop_max();
  while (!heap.is_empty()) {
    int next_max = heap.pop_max();
    ASSERT_TRUE(max >= next_max);
    max = next_max;
  }
}

TEST(MAXHEAP, sol4) {
  MaxHeap heap{};
  heap.add(1).add(2).add(3).add(4);
  ASSERT_EQ(4, heap.pop_max());
  ASSERT_EQ(3, heap.pop_max());
  ASSERT_EQ(2, heap.pop_max());
  ASSERT_EQ(1, heap.pop_max());
  ASSERT_EQ(0, heap.pop_max());
}
TEST(MAXHEAP, sol5) {
  MaxHeap heap{};
  heap.add(4).add(3).add(2).add(1);

  int max = heap.pop_max();
  while (!heap.is_empty()) {
    int next_max = heap.pop_max();
    ASSERT_TRUE(max >= next_max);
    max = next_max;
  }
}

// TEST(MAXHEAP, Timeout)
// {
//     const int N = 100000;
//     MaxHeap heap{};
//     std::random_device rd;
//     std::mt19937 gen{rd()};
//     std::uniform_int_distribution dis{0, std::numeric_limits<int>::max()};
//     for (int i = 0; i < N; ++i)
//     {
//         heap.add(dis.operator()(gen));
//     }
//     int max = heap.pop_max();
//     for (int i = 0; i < N; ++i)
//     {
//         int next_max = heap.pop_max();
//         ASSERT_TRUE(max >= next_max);
//         max = next_max;
//     }
// }

TEST(LIMITS, INT_MAX) {
  ASSERT_EQ(2147483647, std::numeric_limits<int>::max());
}

// __attribute__((noinline, used)) static char *
// to_string(const std::vector<int> &ls) {
//   std::string ret = "";
//   for (const int &e : ls) {
//     ret.append(std::to_string(e) + " ");
//   }
//   return ret.c_str();
// }