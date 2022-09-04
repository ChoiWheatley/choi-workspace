/// https://school.programmers.co.kr/learn/courses/30/lessons/92334
#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k)
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
          words.insert(word);
        }
        ASSERT_EQ(words.size(), 2) << "Each report must have exactly two words!";
      }

      ASSERT_GE(k, 1);
      ASSERT_LE(k, 200);

      auto const answer = solution(id_list, report, k);
      EXPECT_EQ(result, answer);
    }
  }; // class Fixture

  TEST_F(ReportFixture, 1)
  {
    id_list = {"muzi", "frodo", "apeach", "neo"};
    report = {"muzi frodo", "apeach frodo", "frodo neo", "muzi neo", "apeach muzi"};
    k = 2;
    result = {2, 1, 1, 0};

    DoTest();
  }

} // namespace testing