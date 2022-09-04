/// https://school.programmers.co.kr/learn/courses/30/lessons/92334
#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

static vector<int> solution(vector<string> id_list, vector<string> report, int k)
{
  vector<int> answer;
  return answer;
}

namespace testing
{
  class ReportFixture : public Test
  {
  protected:
    vector<string> id_list;
    vector<string> report;
    int k;
    vector<int> result;

    auto DoTest() -> void
    {
      ASSERT_GE(id_list.size(), 2);
      ASSERT_LE(id_list.size(), 1000);
      set<string> id_set;
      for (const auto &id : id_list)
      {
        ASSERT_GE(id.size(), 1);
        ASSERT_LE(id.size(), 10);
        // no duplicated elements
        auto [iter, success] = id_set.insert(id);
        ASSERT_TRUE(success);
      }

      ASSERT_GE(report.size(), 1);
      ASSERT_LE(report.size(), 200000);
      for (const auto &each : report)
      {
        ASSERT_GE(each.size(), 3);
        ASSERT_LE(each.size(), 21);
        // only two splitted words
        set<string> words;
        auto input = istringstream{each};
        for (string word; std::getline(input, word, ' ');)
        {
          ASSERT_NE(id_set.find(word), id_set.end());
          words.insert(word);
        }
        ASSERT_EQ(words.size(), 2) << "Each report must have exactly two words!";
      }

      ASSERT_GE(k, 1);
      ASSERT_LE(k, 200);

      ASSERT_EQ(result.size(), id_list.size());

      auto const answer = solution(id_list, report, k);
      EXPECT_EQ(result, answer);
    }
  }; // class Fixture

  // TEST_F(ReportFixture, WrongTestCase)
  // {
  //   id_list = {"a", "b", "c"};
  //   report = {"a d"};
  //   k = 3;
  //   result = {0, 0, 0};

  //   DoTest();
  // }

  TEST_F(ReportFixture, 1)
  {
    id_list = {"muzi", "frodo", "apeach", "neo"};
    report = {"muzi frodo", "apeach frodo", "frodo neo", "muzi neo", "apeach muzi"};
    k = 2;
    result = {2, 1, 1, 0};

    DoTest();
  }

  /// ryan이 con을 4번 신고했으나 한 유저가 같은 유저를 여러 번 신고한 경우는 1회로 처리한다.
  TEST_F(ReportFixture, 2)
  {
    id_list = {"con", "ryan"};
    report = {"ryan con", "ryan con", "ryan con", "ryan con"};
    k = 3;
    result = {0, 0};

    DoTest();
  }

} // namespace testing