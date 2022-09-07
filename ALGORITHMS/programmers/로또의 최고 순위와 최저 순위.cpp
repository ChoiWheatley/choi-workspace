#include <algorithm>
#include <array>
#include <cmath>
#include <functional>
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

static constexpr size_t MIN_LOTTO = 0;
static constexpr size_t MAX_LOTTO = 45;
static constexpr size_t LOTTO_CNT = 6;

// when hit count is bigger than LOTTO_CNT, it is undefined behavior
static auto HitCountToRank(size_t hit) -> size_t
{
  return (LOTTO_CNT - hit + 1);
}

static auto RankToHitCount(size_t rank) -> size_t
{
  return (LOTTO_CNT - rank + 1);
}

// from range [l, r)
template <typename _T>
static auto mergeSort(vector<_T> &sorting, vector<size_t> &indices, size_t l, size_t r) -> void
{
  // halt condition
  if (!(l < r))
  {
    return;
  }
  auto const mid = static_cast<size_t>(ceil((l + r) / 2.0));
  mergeSort(sorting, indices, l, mid);
  mergeSort(sorting, indices, mid, r);
  // merge l to r
  auto leftCursor = l;
  auto rightCursor = mid;
  vector<_T> tmpSorting;
  vector<size_t> tmpIndices;
  while ((leftCursor < mid) && (rightCursor < r))
  {
    auto const leftElem = sorting[leftCursor];
    auto const rightElem = sorting[rightCursor];
    if (rightElem < leftElem)
    {
      tmpSorting.push_back(rightElem);
      tmpIndices.push_back(rightCursor);
      ++rightCursor;
    }
    else
    {
      tmpSorting.push_back(leftElem);
      tmpIndices.push_back(leftCursor);
      ++leftCursor;
    }
  }
  // remain?
  if (leftCursor < mid)
  {
    tmpSorting.push_back(sorting[leftCursor]);
    tmpIndices.push_back(leftCursor);
  }
  if (rightCursor < r)
  {
    tmpSorting.push_back(sorting[rightCursor]);
    tmpIndices.push_back(rightCursor);
  }
  // finally do move
  sorting = move(tmpSorting);
};

// merge sort
template <typename _T>
static auto Sort(vector<_T> &&vec) -> pair<vector<_T> & /*sorted*/, vector<size_t> /*index*/>
{
  auto sorting = vector<_T>(move(vec));
  auto indices = vector<size_t>{};
  for (size_t i = 0; i < sorting.size(); ++i)
  {
    indices.push_back(i);
  }
  mergeSort(sorting, indices, 0, sorting.size());
  return {sorting, indices};
}

// 몇 개 맞췄는지 보고, 그 다음에 와일드카드가 각각 모두 정답인 경우와
// 모두 오답인 경우에 대한 점수차이를 오프셋한다.
static auto solution(vector<int> lottos, vector<int> win_nums) -> vector<int>
{
}

namespace testing
{
  TEST(Sorting, Basic)
  {
    auto before = vector<int>{5, 4, 3, 2, 1};
    auto const [sorted, indices] = Sort(move(before));
  }
  class 로또Fixture : public Test
  {
  public:
    using _LottoType = array<int, LOTTO_CNT>;

    _LottoType lottos;
    _LottoType win_nums;
    pair<int, int> answer;

  protected:
    로또Fixture()
    {
      lottos.fill(0);
      win_nums.fill(0);
      answer = {0, 0};
    }
    void DoTest()
    {
      for (auto const &i : lottos)
      {
        ASSERT_GE(i, MIN_LOTTO);
        ASSERT_LE(i, MAX_LOTTO);
      }
      for (auto const &i : win_nums)
      {
        ASSERT_GE(i, MIN_LOTTO);
        ASSERT_LE(i, MAX_LOTTO);
      }
      ASSERT_TRUE(IsNotDuplicated(lottos));
      ASSERT_TRUE(IsNotDuplicated(win_nums));

      auto const answer_vec = vector<int>{answer.first, answer.second};
      auto const lottos_vec = vector<int>(lottos.begin(), lottos.end());
      auto const win_nums_vec = vector<int>(win_nums.begin(), win_nums.end());

      ASSERT_EQ(answer_vec, solution(lottos_vec, win_nums_vec));
    }

  private:
    static auto IsNotDuplicated(const _LottoType &lottos, size_t except = 0) -> AssertionResult
    {
      for (size_t i = 0; i < lottos.size(); ++i)
      {
        auto const &sample = lottos.at(i);
        if (sample == except)
          continue;
        for (size_t j = i + 1; j < lottos.size(); ++j)
        {
          if (sample == lottos.at(j))
          {
            stringstream error_msg;
            error_msg << "in { ";
            for (auto const &l : lottos)
            {
              error_msg << l << ", ";
            }
            error_msg << "}, " << sample << " is duplicated.";
            return AssertionFailure() << error_msg.str();
          }
        }
      }
      return AssertionSuccess();
    };
  }; // 로또Fixture

  // TEST_F(로또Fixture, BadCase)
  // {
  //   lottos = {1, 1};
  // }

  TEST_F(로또Fixture, 1)
  {
    lottos = {44, 1, 0, 0, 31, 25};
    win_nums = {31, 10, 45, 1, 6, 19};
    answer = {3, 5};

    DoTest();
  }

  TEST_F(로또Fixture, 2)
  {
    lottos = {0, 0, 0, 0, 0, 0};
    win_nums = {38, 19, 20, 40, 15, 25};
    answer = {1, 6};

    DoTest();
  }

  TEST_F(로또Fixture, 3)
  {
    lottos = {45, 4, 35, 20, 3, 9};
    win_nums = {20, 9, 3, 45, 4, 35};
    answer = {1, 1};

    DoTest();
  }
} // namespace test