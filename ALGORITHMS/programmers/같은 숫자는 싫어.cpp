#include <algorithm>
#include <cassert>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

using namespace std;

constexpr int NAN = -1;

vector<int> solution(vector<int> arr)
{
  vector<int> answer;

  int prev = NAN;
  for (auto const &elem : arr)
  {
    if (elem != prev)
    {
      answer.push_back(elem);
    }
    prev = elem;
  }

  return answer;
}