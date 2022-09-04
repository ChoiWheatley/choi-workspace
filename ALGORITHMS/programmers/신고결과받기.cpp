/// https://school.programmers.co.kr/learn/courses/30/lessons/92334
#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

using IndexMap = unordered_map<string /*id*/, size_t /*idx*/>;

/// @brief simply contains two strings, reporting id and be reported id
struct Report
{
  string id;
  string to;
  bool operator==(const Report &other) const
  {
    return (id == other.id && to == other.to);
  }
}; // struct Report

struct ReportWithIdx : public Report
{
  size_t id_idx;
  size_t to_idx;
  bool operator==(const ReportWithIdx &other) const
  {
    return (id == other.id && to == other.to) &&
           (id_idx == other.id_idx && to_idx == other.to_idx);
  }
  ReportWithIdx(string id, size_t id_idx, string to, size_t to_idx)
      : Report{.id = id, .to = to}, id_idx{id_idx}, to_idx{to_idx} {}
}; // ReportWithIdx

/// @brief Parse string that contains reporter and reportee splitted by whitespace
/// @param str 'a b' means `a` reported `b`
static auto ParseReport(const string &str) -> Report
{
  auto words = vector<string>{};
  auto input_stream = istringstream{str};
  for (string word; std::getline(input_stream, word, ' ');)
  {
    words.push_back(word);
  }
  return Report{.id = words[0], .to = words[1]};
}

static vector<int> solution(vector<string> id_list, vector<string> report, int k)
{
  auto answer = vector<int>{static_cast<int>(id_list.size()), 0};

  auto const indexMap = [id_list]() -> IndexMap
  {
    IndexMap ret;
    for (size_t idx = 0; idx < id_list.size(); ++idx)
    {
      ret.insert({id_list[idx], idx});
    }
    return ret;
  }();

  auto const reports = [report]() -> vector<Report>
  {
    vector<Report> ret;
    for (auto const &r : report)
    {
      ret.push_back(ParseReport(r));
    }
    return ret;
  }();

  auto const reportWithIndex = [reports, indexMap]() -> vector<ReportWithIdx>
  {
    vector<ReportWithIdx> ret;
    for (Report const &r : reports)
    {
      ret.push_back(ReportWithIdx{
          r.id, indexMap.at(r.id),
          r.to, indexMap.at(r.to)});
    }
    return ret;
  }();

  return answer;
}

namespace testing
{
  TEST(ParseString, ParseReport)
  {
    auto const str = "muzi frodo";
    auto const ans = Report{"muzi", "frodo"};
    EXPECT_EQ(ans, ParseReport(str));
  }

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